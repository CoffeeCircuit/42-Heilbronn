# GitHub Copilot Instructions - Call Me Maybe Project

## Project Overview

This is a function calling system that converts natural language prompts into structured JSON function calls using constrained decoding with small LLMs (Qwen/Qwen3-0.6B).

## Critical Requirements

### ✅ ALLOWED Packages
- `pydantic` (REQUIRED for all validation)
- `numpy`
- `json`
- `llm_sdk` (provided package - only public methods/attributes)

### ❌ FORBIDDEN Packages
- dspy
- pytorch
- huggingface
- transformers
- outlines
- Any similar LLM frameworks

## Core Principles

### 1. Pydantic Validation
**ALL classes must use pydantic for validation**. Every data structure should be a pydantic model.

```python
from pydantic import BaseModel

class FunctionCall(BaseModel):
    prompt: str
    name: str
    parameters: dict
```

### 2. Constrained Decoding (NOT Prompting)
- Function selection MUST use LLM with constrained decoding
- DO NOT rely on the model spontaneously producing correct JSON from prompts
- DO NOT use heuristics or rule-based function selection
- Modify logits to enforce valid JSON structure and schema compliance
- Set invalid token logits to negative infinity
- Guarantee 100% valid, parseable JSON output

### 3. LLM SDK Usage
Only use these public methods from `llm_sdk.Small_LLM_Model`:
- `get_logits_from_input_ids(input_ids: Tensor) -> Tensor`
- `get_path_to_vocabulary_json() -> str`
- `encode(text: str) -> List[int]`
- `decode(token_ids: List[int]) -> str` (optional)

**Never access private methods or attributes (no `_method` or `__attribute__`).**

### 4. Error Handling
- Handle all errors gracefully
- Provide clear error messages
- Never crash unexpectedly
- Handle: malformed JSON, missing files, invalid schemas, edge cases

## Input/Output Format

### Input Files
1. **function_calling_tests.json**: Array of `{"prompt": "..."}` objects
2. **functions_definition.json**: Array of function schemas with name, description, parameters, returns

### Output File
**function_calling_results.json**: Array of objects with:
```json
{
  "prompt": "original prompt",
  "name": "function_name",
  "parameters": {"arg1": value1, "arg2": value2}
}
```

**Validation Rules:**
- Valid JSON (no trailing commas, no comments)
- Exact key/type matching with schema
- No extra keys or prose
- All required arguments present
- Correct argument types (number, string, boolean, etc.)

## Command Line Interface

```bash
uv run python -m src [--functions_definition <file>] [--input <file>] [--output <file>]
```

Defaults:
- functions_definition: `data/input/functions_definition.json`
- input: `data/input/function_calling_tests.json`
- output: `data/output/function_calling_results.json`

## Implementation Strategy

### Constrained Decoding Process
1. Get logits from LLM for current token position
2. Load vocabulary JSON to map token IDs to strings
3. Determine which tokens maintain valid JSON structure AND schema compliance
4. Set logits to -inf for invalid tokens
5. Sample from remaining valid tokens
6. Repeat token-by-token until complete

### Key Considerations
- Use vocabulary JSON to determine valid tokens at each step
- Track JSON state (in object, in array, in string, key vs value, etc.)
- Enforce schema constraints (allowed function names, parameter types, etc.)
- Build output incrementally, validating at each step

## Performance Targets

- **Accuracy**: 90%+ correct function selection and argument extraction
- **JSON Validity**: 100% parseable and schema-compliant
- **Speed**: Process all prompts in under 5 minutes
- **Reliability**: Robust error handling for all edge cases

## Code Style

### Type Hints
Always use type hints:
```python
def process_prompt(prompt: str, functions: list[dict]) -> FunctionCall:
    ...
```

### Pydantic Models
Use pydantic for all data structures:
```python
class FunctionDefinition(BaseModel):
    name: str
    description: str
    parameters: dict[str, dict]
    returns: dict
```

### Error Handling Pattern
```python
try:
    # operation
except SpecificError as e:
    logger.error(f"Clear message: {e}")
    # graceful recovery or informative exit
```

## Testing Edge Cases

Always consider:
- Empty strings
- Large numbers
- Special characters in strings
- Wrong/missing types
- Ambiguous prompts
- Functions with multiple parameters
- Malformed/missing input files
- Invalid function definitions

## Don't Hardcode

Input files may change during evaluation. Never hardcode:
- Specific function names
- Expected prompts
- Parameter values
- Number of functions

All logic must be dynamic and based on the provided function definitions.

## Architecture Hints

Suggested modules:
- `models.py`: Pydantic models for validation
- `decoder.py`: Constrained decoding logic
- `generator.py`: Token-by-token generation with constraints
- `vocabulary.py`: Vocabulary JSON parsing and token utilities
- `main.py`: CLI entry point, orchestration

Remember: The power is in the constraints, not the model size.

## Testing and debugging 
- Durring testing and debugging, the program running time should at most 5 min
- The program should outpout running time at the the end 
- Do not use `head` or `tail` to pipe the outpu. 
