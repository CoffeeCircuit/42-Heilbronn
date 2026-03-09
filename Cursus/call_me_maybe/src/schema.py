from typing import Set
from pydantic import BaseModel, Field
from src.models import FunctionDefinition


class SchemaValidator(BaseModel):
    """Validates tokens against function schemas."""

    functions: list[FunctionDefinition]
    current_function_name: str = ""
    keys_seen: Set[str] = Field(
        default_factory=set
    )  # Track which top-level keys we've seen
    parameters_seen: Set[str] = Field(
        default_factory=set
    )  # Track which parameters we've added

    class Config:
        arbitrary_types_allowed = True

    def get_valid_tokens_semantic(
        self,
        current_key: str,
        current_value: str,
        vocab_tokens: Set[str],
        in_string: bool = False,
        is_expecting_key: bool = False,
        is_expecting_value: bool = False,
        depth: int = 0,
    ) -> Set[str]:
        """Returns semantically valid tokens based on schema.

        Args:
            current_key: The current JSON key being processed
            current_value: The value being built
            vocab_tokens: Set of structurally valid tokens from FSM
            in_string: Whether we're currently inside a string
            is_expecting_key: Whether FSM is in EXPECT_KEY state
            is_expecting_value: Whether FSM is in EXPECT_VALUE state
            depth: Current nesting depth
        """

        # When we're building a key name at top level (no current key yet,
        # inside string, expecting key)
        if not current_key and in_string and is_expecting_key:
            # Check depth to determine if we're at top level or in parameters
            if depth == 1:
                # Top level - constrain to "name", "parameters"
                return self._filter_valid_keys(current_value, vocab_tokens)
            else:
                # Inside parameters object - constrain to valid parameter names
                return self._filter_parameter_keys(current_value, vocab_tokens)

        # When we're building the function name value
        if current_key == "name" and in_string:
            return self._filter_function_names(current_value, vocab_tokens)

        elif current_key == "parameters" and is_expecting_value:
            # Parameters value must be an object - only allow {
            return {"{", " ", "\n", "\t"} & vocab_tokens

        elif self.current_function_name and current_key:
            # We're inside parameters - constrain based on parameter type
            if in_string:
                # Building a string value
                return self._filter_parameter_value(
                    current_key, current_value, vocab_tokens
                )
            elif is_expecting_value:
                # About to generate a value - check parameter type
                func = next(
                    (
                        f
                        for f in self.functions
                        if f.name == self.current_function_name
                    ),
                    None,
                )
                if func and current_key in func.parameters:
                    param_type = func.parameters[current_key].get(
                        "type", "string"
                    )
                    if param_type in ["number", "integer"]:
                        structural_no_quote = vocab_tokens - {'"'}
                        return structural_no_quote
                    elif param_type == "boolean":
                        # Don't allow quotes for boolean
                        structural_no_quote = vocab_tokens - {'"'}
                        return {
                            "t",
                            "f",
                            "true",
                            "false",
                            " ",
                            "\n",
                            "\t",
                            ",",
                            "}",
                        } & structural_no_quote
                    elif param_type == "string":
                        return {'"', " ", "\n", "\t"} & vocab_tokens
                # For unknown types, allow quotes
                return vocab_tokens

        # For any other case, only allow structural tokens
        # But prevent closing main object until we have both
        # "name" and "parameters"
        structural = {'"', ":", ",", "}", "]", " ", "\n", "\t"} & vocab_tokens

        required_keys = {"name", "parameters"}
        if depth == 1:
            if (
                not required_keys.issubset(self.keys_seen)
                and "}" in structural
            ):
                structural.discard("}")
            # Don't allow comma at depth 1 if we already have both keys
            if required_keys.issubset(self.keys_seen) and "," in structural:
                structural.discard(",")
            if required_keys.issubset(self.keys_seen) and '"' in structural:
                structural.discard('"')
        elif depth == 2 and self.current_function_name:
            if "}" in structural and len(self.parameters_seen) == 0:
                # Must add at least one parameter
                structural.discard("}")

            # Get required parameters for this function
            func = next(
                (
                    f
                    for f in self.functions
                    if f.name == self.current_function_name
                ),
                None,
            )
            if func:
                required_params = set(func.parameters.keys())
                if "}" in structural and not required_params.issubset(
                    self.parameters_seen
                ):
                    structural.discard("}")
                # Don't allow comma if we already have all parameters
                if "," in structural and required_params.issubset(
                    self.parameters_seen
                ):
                    structural.discard(",")
                if '"' in structural and required_params.issubset(
                    self.parameters_seen
                ):
                    structural.discard('"')

        return structural

    def set_function_name(self, name: str) -> None:
        """Set the current function name after it's been generated."""
        self.current_function_name = name

    def mark_key_complete(self, key: str) -> None:
        """Mark a top-level key as complete."""
        self.keys_seen.add(key)

    def mark_parameter_complete(self, param_name: str) -> None:
        """Mark a parameter as complete."""
        self.parameters_seen.add(param_name)

    def reset_state(self, prompt: str = "") -> None:
        """Reset state between function calls."""
        self.current_function_name = ""
        self.keys_seen = set()
        self.parameters_seen = set()

    def _filter_valid_keys(
        self, current_value: str, vocab_tokens: Set[str]
    ) -> Set[str]:
        """Filter tokens that continue toward valid JSON keys
        ('name', 'parameters')."""
        valid_keys = {"name", "parameters"}
        # Exclude keys we've already seen
        valid_keys = valid_keys - self.keys_seen

        if not valid_keys:
            return set()

        valid_tokens = set()

        for key in valid_keys:
            if key.startswith(current_value):
                remaining = key[len(current_value):]

                if not remaining:
                    if '"' in vocab_tokens:
                        valid_tokens.add('"')
                    continue

                # Check which vocab tokens are valid continuations
                for token in vocab_tokens:
                    # Don't allow closing quote unless key is complete
                    if token == '"' and current_value != key:
                        continue
                    if remaining.startswith(token):
                        valid_tokens.add(token)
                    # Early exit if we have enough tokens
                    if len(valid_tokens) > 50:
                        break

        # If no valid tokens found, allow all vocab tokens (fallback)
        # This handles vocabulary mismatches
        if not valid_tokens:
            valid_tokens = vocab_tokens - {
                '"'
            }  # Don't allow premature closing

        return valid_tokens

    def _filter_parameter_keys(
        self, current_value: str, vocab_tokens: Set[str]
    ) -> Set[str]:
        """Filter tokens that continue toward valid parameter
        names for current function."""
        if not self.current_function_name:
            return vocab_tokens

        # Get function definition
        func = next(
            (
                f
                for f in self.functions
                if f.name == self.current_function_name
            ),
            None,
        )
        if not func:
            return vocab_tokens

        # Filter out parameters we've already seen
        remaining_params = set(func.parameters.keys()) - self.parameters_seen

        # If no parameters left, return empty set to prevent starting new keys
        if not remaining_params:
            return set()

        valid_tokens = set()

        for param_name in remaining_params:
            if param_name.startswith(current_value):
                remaining = param_name[len(current_value):]

                if not remaining:
                    if '"' in vocab_tokens:
                        valid_tokens.add('"')
                    continue

                for token in vocab_tokens:
                    if token == '"' and current_value != param_name:
                        continue
                    if remaining.startswith(token):
                        valid_tokens.add(token)
                    # Early exit
                    if len(valid_tokens) > 50:
                        break

        # If no valid tokens found (vocabulary mismatch), allow all but quote
        if not valid_tokens:
            valid_tokens = vocab_tokens - {'"'}

        return valid_tokens

    def _filter_function_names(
        self, current_value: str, vocab_tokens: Set[str]
    ) -> Set[str]:
        """Filter tokens that continue toward valid function names."""
        valid_tokens = set()

        for func in self.functions:
            fn_name = func.name
            if fn_name.startswith(current_value):
                remaining = fn_name[len(current_value):]

                # If remaining is empty, just allow closing quote
                if not remaining:
                    if '"' in vocab_tokens:
                        valid_tokens.add('"')
                    continue

                for token in vocab_tokens:
                    if token == '"' and current_value != fn_name:
                        continue
                    if remaining.startswith(token):
                        valid_tokens.add(token)
                    # Early termination: if we have enough valid tokens, stop
                    if len(valid_tokens) > 50:
                        break

        # If no valid tokens found, allow all but quote
        if not valid_tokens:
            valid_tokens = vocab_tokens - {'"'}

        return valid_tokens

    def _filter_parameter_value(
        self, param_name: str, current_value: str, vocab_tokens: Set[str]
    ) -> Set[str]:
        """Filter tokens based on parameter type."""
        func = next(
            (
                f
                for f in self.functions
                if f.name == self.current_function_name
            ),
            None,
        )
        if not func or param_name not in func.parameters:
            return vocab_tokens

        param_def = func.parameters[param_name]
        param_type = param_def.get("type", "string")

        if param_type == "number" or param_type == "integer":
            # Allow digits and decimal point
            valid_tokens = set()
            for token in vocab_tokens:
                if token.isdigit() or (
                    token == "." and "." not in current_value
                ):
                    valid_tokens.add(token)
                # Allow comma or } after we have at least one digit
                if current_value and (token == "," or token == "}"):
                    valid_tokens.add(token)
            return valid_tokens if valid_tokens else vocab_tokens

        elif param_type == "boolean":
            valid = set()
            for target in ["true", "false"]:
                if target.startswith(current_value):
                    remaining = target[len(current_value):]
                    for token in vocab_tokens:
                        if remaining.startswith(token):
                            valid.add(token)
            return valid if valid else vocab_tokens

        # For strings and other types, allow all tokens
        return vocab_tokens
