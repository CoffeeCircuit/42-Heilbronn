*This project has been created as part of the 42 curriculum by abalcu*

# Call Me Maybe - Constrained Decoding for Function Calling

## Description

This project implements a function calling system that converts natural language prompts into structured JSON function calls using constrained decoding with a small language model (Qwen3-0.6B). Unlike traditional prompt-based approaches that rely on the model to spontaneously produce valid JSON, this implementation uses **constrained decoding** to guarantee 100% valid, schema-compliant JSON output by manipulating logits at each generation step.

### Key Features:
- **Guaranteed Valid JSON**: Uses finite state machines and schema validation to ensure structural correctness
- **Schema Compliance**: Enforces function signatures, parameter types, and required fields
- **Small Model**: Achieves reliable results with only a 0.6B parameter model
- **No External Frameworks**: Built from scratch using only `pydantic`, `numpy`, and the provided LLM SDK

### Goal:
Generate valid function calls from natural language by constraining the model's token generation space at each step, ensuring both syntactic (JSON structure) and semantic (schema) validity.

## Instructions

### Prerequisites
- Python 3.10+
- `uv` package manager

### Installation
```bash
# Clone the repository
git clone <repository-url>
cd call_me_maybe

# Install dependencies (uv will create a virtual environment automatically)
make install
```

### Running the Program
```bash
# Run with default input/output files
uv run -m src

# Or specify custom files
uv run -m src --functions_definition data/input/functions_definition.json \
               --input data/input/function_calling_tests.json \
               --output data/output/function_calling_results.json
```

### Using Makefile
```bash
make run      # Run the program
make clean    # Clean output files
```

## Algorithm Explanation

### Constrained Decoding Architecture

The system uses a three-layer architecture to constrain token generation:

#### 1. **Finite State Machine (FSM)** - Structural Validation
Located in `src/fsm.py`, the FSM tracks JSON parsing state:
- States: `EMPTY`, `OBJ_START`, `EXPECT_KEY`, `EXPECT_SEP`, `EXPECT_VALUE`, `AFTER_VALUE`, `OBJ_END`
- Ensures syntactic correctness: proper brace matching, quote placement, comma/colon positioning
- Filters vocabulary to only allow structurally valid tokens at each step

#### 2. **Schema Validator** - Semantic Validation
Located in `src/schema.py`, validates against function definitions:
- Constrains key names to `"name"` and `"parameters"` at top level
- Enforces valid function names from the schema
- Ensures parameter names match function signature
- Validates parameter types (string, number, boolean)
- Prevents premature closing before all required fields are present

#### 3. **Constrained Decoder** - Integration Layer
Located in `src/decoder.py`, combines FSM and schema:
```python
valid_tokens = FSM_valid_tokens ∩ Schema_valid_tokens
masked_logits[invalid_tokens] = -∞
```

### Generation Flow
```
1. Encode prompt + function definitions
2. For each token position:
   a. Get logits from LLM
   b. Apply FSM constraints (structural)
   c. Apply schema constraints (semantic)
   d. Mask invalid token logits to -∞
   e. Sample from remaining valid tokens (greedy)
   f. Update FSM and schema state
   g. Decode and append token
3. Decode token IDs to final JSON string
```

### Token Decoding
Raw tokens like `Ġ` (space) and `Ċ` (newline) are handled by accumulating token IDs during generation and using the model's `decode()` method at the end to convert them to proper characters.

## Design Decisions

### 1. **Pydantic for All Data Structures**
Every class uses Pydantic models for automatic validation:
```python
class FunctionCall(BaseModel):
    prompt: str
    name: str
    parameters: dict
```
This ensures type safety and clear contracts between components.

### 2. **Separation of Concerns**
- `fsm.py`: Pure structural JSON validation
- `schema.py`: Pure semantic function schema validation  
- `decoder.py`: Combines both layers
- `generator.py`: Orchestrates the generation loop
- `vocabulary.py`: Handles tokenizer vocabulary operations

### 3. **Performance Optimizations**
- Early loop termination in token filters (limit to 50 valid tokens)
- Cached vocabulary token set
- Efficient string matching for function/parameter names
- Greedy sampling (no beam search overhead)

### 4. **Error Handling**
- Graceful fallback when no valid tokens found
- JSON repair for incomplete generations
- Comprehensive error messages for debugging

## Performance Analysis

### Accuracy
- **9/11 tests (82%)** produce correct function calls with accurate parameters
- **2/11 tests** (greet function) have semantic extraction issues - model limitation, not decoding issue
- **100% valid JSON** - no malformed output

### Speed
- ~8 minutes for 11 test cases on CPU
- ~0.17s per model inference call
- Bottleneck: transformer forward passes, not constraint checking
- Each test requires ~20-40 tokens, growing context slows later tokens

### Reliability
- Deterministic: same prompt always produces same output (greedy sampling)
- Robust: handles edge cases like special characters, large numbers, complex regex patterns
- No crashes or hangs after optimization

## Challenges Faced

### 1. **Performance Bottleneck in Token Filtering**
**Problem**: Initial implementation had nested loops over 151k vocabulary tokens, causing system to hang (5+ minutes per token).

**Solution**: 
- Added early termination when 50 valid tokens found
- Optimized string matching logic
- Reduced from O(vocab_size × functions × params) to O(min(50, valid_tokens))

### 2. **Raw Token Display**
**Problem**: Tokens like `Ġ` (space) and `Ċ` (newline) appeared in output.

**Solution**:
- Accumulate token IDs during generation
- Use model's `decode()` method at end
- Properly converts tokenizer representations to actual characters

### 3. **Context Length Growth**
**Problem**: Appending each token to input_ids made inference progressively slower.

**Solution**: Keep full context (trimming broke model accuracy) but accept the slowdown as fundamental to autoregressive generation.

### 4. **Semantic Extraction Limitations**
**Problem**: Model generates "fn_greet" instead of extracting "shrek" from "Greet shrek".

**Root Cause**: Constrained decoding enforces structure, not semantics. The 0.6B model is too small to reliably extract information from prompts.

**Mitigation**: Improved prompt with better examples, but fundamental limitation remains.

## Testing Strategy

### Unit Testing Approach
- Tested FSM state transitions individually
- Validated schema filtering for each parameter type
- Verified token decoding with special characters

### Integration Testing
```bash
# Test single case for debugging
python test_single.py

# Performance testing
python test_performance.py  # Measures model inference speed
```

### Validation
- Compare output against expected function calls
- Verify JSON validity with `json.loads()`
- Check schema compliance (all required parameters present)
- Validate parameter types match schema definitions

### Edge Cases Tested
- Large numbers (265, 345, 144, 233)
- Special characters in strings (apostrophes, quotes)
- Regex patterns with character classes and groups
- Multiple parameter functions
- Empty vs. populated parameter objects

## Example Usage

### Input Format
**functions_definition.json**:
```json
[
  {
    "name": "fn_add_numbers",
    "description": "Add two numbers together and return their sum.",
    "parameters": {
      "a": {"type": "number"},
      "b": {"type": "number"}
    },
    "returns": {"type": "number"}
  }
]
```

**function_calling_tests.json**:
```json
[
  {"prompt": "What is the sum of 2 and 3?"}
]
```

### Output Format
**function_calling_results.json**:
```json
[
  {
    "prompt": "What is the sum of 2 and 3?",
    "name": "fn_add_numbers",
    "parameters": {
      "a": 2.0,
      "b": 3.0
    }
  }
]
```

### Running Examples
```bash
# Default run
uv run -m src

# Custom input file
uv run -m src --input my_tests.json --output my_results.json

# Different function definitions
uv run -m src --functions_definition custom_functions.json
```

### Sample Output
```
🔄 Processing 11 test cases...

[1/11]
   What is the sum of 2 and 3?...{"name":"fn_add_numbers","parameters":{"a":2.0,"b":3.0}}
 → {"name":"fn_add_numbers","parameters":{"a":2.0,"b":3.0}}

[2/11]
   Reverse the string 'hello'...{"name":"fn_reverse_string","parameters":{"s":"hello"}}
 → {"name":"fn_reverse_string","parameters":{"s":"hello"}}
```

## Resources

### Documentation
- [Pydantic Documentation](https://docs.pydantic.dev/) - Used for all data validation
- [NumPy Documentation](https://numpy.org/doc/) - Used for logit manipulation
- [JSON Specification](https://www.json.org/) - Reference for FSM implementation
- [Qwen3 Model Card](https://huggingface.co/Qwen/Qwen3-0.6B) - Model documentation

### Key Concepts
- **Constrained Decoding**: Technique to guide LLM generation by restricting valid token choices
- **Finite State Machines**: Used to model JSON parsing states
- **Schema Validation**: Ensuring generated output matches predefined structure
- **Logit Masking**: Setting invalid token probabilities to -∞ to prevent selection

### AI Usage
AI tools (GitHub Copilot, Claude) were used for:
- **Code optimization**: Identifying performance bottlenecks in token filtering loops
- **Debugging**: Analyzing hang issues and infinite loops
- **Documentation**: Formatting and structuring README content
- **Error handling**: Suggesting graceful fallback strategies

All core algorithm design (FSM, schema validation, constrained decoding) was human-designed. AI assisted with implementation details and optimization.

### Articles & Tutorials
- "Constrained Decoding for Neural Text Generation" - Academic background
- "JSON Parsing with State Machines" - FSM design patterns
- "Type-Constrained Decoding" - Schema validation techniques

## Project Structure
```
call_me_maybe/
├── src/
│   ├── __init__.py
│   ├── __main__.py          # Entry point
│   ├── decoder.py            # Combines FSM + schema constraints
│   ├── fsm.py                # JSON finite state machine
│   ├── generator.py          # Generation loop orchestration
│   ├── models.py             # Pydantic data models
│   ├── schema.py             # Schema validation logic
│   └── vocabulary.py         # Token vocabulary handling
├── data/
│   ├── input/
│   │   ├── functions_definition.json
│   │   └── function_calling_tests.json
│   └── output/
│       └── function_calling_results.json
├── llm_sdk/                  # Provided LLM package
├── pyproject.toml            # Dependencies
├── Makefile                  # Build automation
└── README.md                 # This file
```

## License
Educational project for 42 School curriculum.
