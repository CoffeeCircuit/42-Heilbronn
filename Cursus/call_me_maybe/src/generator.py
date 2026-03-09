import numpy as np
from typing import Any
from pydantic import BaseModel
from src.fsm import JSONState
from src.decoder import ConstrainedDecoder
from src.models import FunctionCall


class ConstrainedGenerator(BaseModel):
    """Generates function calls using constrained decoding."""

    decoder: ConstrainedDecoder
    model: Any  # Small_LLM_Model instance

    class Config:
        arbitrary_types_allowed = True

    def generate_function_call(
        self, prompt: str, max_tokens: int = 100
    ) -> FunctionCall:
        """
        Generate a function call from a natural language prompt.

        Args:
            prompt: Natural language question
            max_tokens: Maximum tokens to generate

        Returns:
            FunctionCall with name and parameters
        """
        # Reset schema validator state at start of generation
        self.decoder.schema_validator.reset_state()

        # Find EOS token ID
        eos_token_id = None
        eos_candidates = [
            "<|endoftext|>",
            "</s>",
            "<eos>",
            "<|im_end|>",
            "<|end|>",
        ]
        for token_str, token_id in self.decoder.vocab.token_to_id.items():
            if token_str in eos_candidates:
                eos_token_id = token_id
                break

        # Build function definitions with descriptions
        functions_text = "Available functions:\n"
        for func in self.decoder.schema_validator.functions:
            params = ", ".join(func.parameters.keys())
            description = func.description
            functions_text += f" - {func.name}({params}): {description}\n"

        # Build example outputs
        examples_text = "\nExample output:\n"
        for func in self.decoder.schema_validator.functions:
            # Create example parameters based on types
            example_params: dict[str, Any] = {}
            for param_name, param_schema in func.parameters.items():
                param_type = param_schema.get("type", "string")
                if param_type == "number" or param_type == "integer":
                    example_params[param_name] = (
                        5.0 if param_type == "number" else 5
                    )
                elif param_type == "string":
                    example_params[param_name] = param_name
                elif param_type == "boolean":
                    example_params[param_name] = True

            import json

            example_json = json.dumps(
                {"name": func.name, "parameters": example_params}
            )
            examples_text += f" - {example_json}\n"

        # Combine all parts
        initial_text = f"{functions_text}{examples_text}\nTask: {prompt}\n{{"

        print(f"\n   {prompt[:60]}...", end="", flush=True)

        # print(initial_text)
        # exit()

        encoded = self.model.encode(initial_text)

        # Convert tensor to list - handle both 1D and 2D tensors
        if len(encoded.shape) == 2:
            input_ids = encoded.tolist()[0]
        else:
            input_ids = encoded.tolist()

        # Track generated token IDs for proper decoding
        generated_token_ids = []

        print("{", end="", flush=True)  # Print initial brace

        # Initialize FSM to OBJ_START since we already have {
        self.decoder.fsm.state = JSONState.OBJ_START
        self.decoder.fsm.depth = 1

        for i in range(max_tokens):
            # Get logits from model
            logits_list = self.model.get_logits_from_input_ids(input_ids)

            # Convert to numpy array
            next_token_logits = np.array(logits_list, dtype=np.float32)

            # Apply constraints
            try:
                masked_logits = self.decoder.mask_logits(next_token_logits)
            except Exception as e:
                print(f"\n[ERROR in mask_logits: {e}]", flush=True)
                break

            # Check if all logits are -inf (no valid tokens)
            if np.all(np.isinf(masked_logits)):
                print("\nNo valid tokens", flush=True)
                break

            # Sample (greedy)
            next_token_id = int(np.argmax(masked_logits))

            # Check for EOS token
            if eos_token_id is not None and next_token_id == eos_token_id:
                break

            next_token_str = self.decoder.vocab.id_to_token[next_token_id]

            # Print token in real-time (shows raw tokens like Ġ and Ċ)
            print(next_token_str, end="", flush=True)

            # Add to generated token IDs
            generated_token_ids.append(next_token_id)
            input_ids.append(next_token_id)

            # Update state
            self.decoder.update_after_token(next_token_str)

            # Check for completion - when we close the main object
            if (
                self.decoder.fsm.state == JSONState.OBJ_END
                and self.decoder.fsm.depth == 0
            ):
                break

        # Decode the generated tokens to get properly formatted JSON
        generated_json = "{" + self.model.decode(generated_token_ids)

        # Clean up any trailing whitespace or newlines that might cause issues
        generated_json = generated_json.strip()

        # Ensure JSON is properly closed if incomplete
        try:
            # Try to parse - if it fails, we might need to close brackets
            import json

            json.loads(generated_json)
        except json.JSONDecodeError:
            open_braces = generated_json.count("{")
            close_braces = generated_json.count("}")
            if open_braces > close_braces:
                generated_json += "}" * (open_braces - close_braces)

        # Parse and validate
        import json

        print(f"\n → {generated_json}", flush=True)

        try:
            result = json.loads(generated_json)

            return FunctionCall(
                prompt=prompt,
                name=result.get("name", "unknown"),
                parameters=result.get("parameters", {}),
            )
        except json.JSONDecodeError:
            # Try to extract function name and parameters manually
            import re

            name_match = re.search(r'"name"\s*:\s*"([^"]+)"', generated_json)
            name = name_match.group(1) if name_match else "error"

            return FunctionCall(prompt=prompt, name=name, parameters={})
