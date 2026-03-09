"""Main entry point for constrained function calling system."""

from llm_sdk import Small_LLM_Model  # type: ignore
from argparse import ArgumentParser
import json
from pathlib import Path

from src.models import FunctionDefinition, TestCase, FunctionCall
from src.vocabulary import VocabularyHandler
from src.schema import SchemaValidator
from src.fsm import JSONStateMachine
from src.decoder import ConstrainedDecoder
from src.generator import ConstrainedGenerator


def load_function_definitions(path: str) -> list[FunctionDefinition]:
    """Load function definitions from JSON file."""
    with open(path) as f:
        data = json.load(f)
    return [FunctionDefinition(**fn) for fn in data]


def load_test_cases(path: str) -> list[TestCase]:
    """Load test prompts from JSON file."""
    with open(path) as f:
        data = json.load(f)
    return [TestCase(**case) for case in data]


def save_results(results: list[FunctionCall], path: str) -> None:
    """Save function call results to JSON file."""
    Path(path).parent.mkdir(parents=True, exist_ok=True)
    with open(path, "w") as f:
        json.dump([result.model_dump() for result in results], f, indent=2)


def main() -> None:
    """Main execution flow for constrained function calling."""
    parser = ArgumentParser(
        prog="Call-Me-Maybe",
        description="42 project on constrained decoding of LLMs",
        usage=(
            "uv run -m src [--functions_definition FILE] [--input FILE]"
            " [--output FILE]"
        ),
        epilog="Example: uv run -m src --input data/input/test.json",
    )
    parser.add_argument(
        "--functions_definition",
        metavar="FILE",
        default="data/input/functions_definition.json",
        help="Path to function definitions JSON file (default: %(default)s)",
    )
    parser.add_argument(
        "--input",
        metavar="FILE",
        default="data/input/function_calling_tests.json",
        help="Path to input prompts JSON file (default: %(default)s)",
    )
    parser.add_argument(
        "--output",
        metavar="FILE",
        default="data/output/function_calling_results.json",
        help="Path to output JSON file (default: %(default)s)",
    )
    args = parser.parse_args()

    # Load inputs
    functions = load_function_definitions(args.functions_definition)
    test_cases = load_test_cases(args.input)

    # Initialize model
    model = Small_LLM_Model()

    # Initialize vocabulary handler
    vocab_handler = VocabularyHandler.read(model.get_path_to_vocab_file())

    # Initialize components
    fsm = JSONStateMachine()
    schema_validator = SchemaValidator(functions=functions)
    decoder = ConstrainedDecoder(
        fsm=fsm, schema_validator=schema_validator, vocab=vocab_handler
    )
    generator = ConstrainedGenerator(decoder=decoder, model=model)

    # Process test cases
    results = []

    print(f"\n🔄 Processing {len(test_cases)} test cases...\n")

    for idx, test_case in enumerate(test_cases, 1):
        print(f"[{idx}/{len(test_cases)}]", end="", flush=True)
        try:
            # Reset FSM, decoder, and schema validator state for each
            # new test case
            decoder.fsm = JSONStateMachine()
            decoder.current_value = ""
            decoder.schema_validator.current_function_name = ""
            decoder.schema_validator.keys_seen = set()
            decoder.schema_validator.parameters_seen = set()

            # Generate function call
            result = generator.generate_function_call(
                test_case.prompt, max_tokens=100
            )
            results.append(result)

        except Exception as e:
            print(f" ✗ Error: {e}")
            # Add placeholder result
            results.append(
                FunctionCall(
                    prompt=test_case.prompt, name="error", parameters={}
                )
            )

    # Save results
    save_results(results, args.output)
    print(f"\n✅ Results saved to {args.output}\n")


if __name__ == "__main__":
    main()
