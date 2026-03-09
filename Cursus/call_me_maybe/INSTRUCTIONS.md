# Call Me Maybe - Function Calling in LLMs

A function calling tool that translates natural language prompts into structured function calls using constrained decoding with small language models.

## 📋 Table of Contents

- [Overview](#overview)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Input Files](#input-files)
- [Output Format](#output-format)
- [LLM Interaction](#llm-interaction)
- [Testing](#testing)
- [Performance Requirements](#performance-requirements)

## 🎯 Overview

This project creates a function calling system that transforms natural language prompts into structured function calls. Given a question like **"What is the sum of 40 and 2?"**, the system returns:

- **Function name**: `fn_add_numbers`
- **Arguments**: `{"a": 40, "b": 2}`

The implementation uses **constrained decoding** to guarantee 100% valid JSON output, achieving near-perfect reliability even with a small 0.5B parameter model.

## 📦 Requirements

### Mandatory Dependencies

- **Python 3.x**
- **uv** (package manager)
- **pydantic** (for validation)
- **numpy**
- **json** (built-in)

### Model Requirements

- **Primary Model**: Qwen/Qwen3-0.6B (default)
- Other models may be used as long as the project works with Qwen/Qwen3-0.6B

### Restrictions

The following packages are **FORBIDDEN**:

❌ dspy  
❌ pytorch  
❌ huggingface  
❌ transformers  
❌ outlines  
❌ Any similar LLM frameworks  

### Additional Constraints

- ✅ All classes must use **pydantic** for validation
- ✅ Function selection must use the **LLM**, not heuristics
- ✅ No private methods/attributes from `llm_sdk` package
- ✅ All errors must be handled gracefully with clear error messages
- ✅ Program must never crash unexpectedly

## 🚀 Installation

### 1. Clone the Repository

```bash
git clone <repository-url>
cd call_me_maybe
```

### 2. Create Virtual Environment and Install Dependencies

```bash
uv sync
```

### 3. Set Up llm_sdk

Copy the `llm_sdk` package into the same directory as `src`:

```
call_me_maybe/
├── llm_sdk/
├── src/
├── data/
└── ...
```

## 💻 Usage

### Basic Command

```bash
uv run python -m src
```

### With Custom Paths

```bash
uv run python -m src \
  --functions_definition data/input/functions_definition.json \
  --input data/input/function_calling_tests.json \
  --output data/output/function_calls.json
```

### Default Behavior

- **Input directory**: `data/input/`
- **Output directory**: `data/output/`
- Custom paths can be specified using command-line arguments

## 📁 Project Structure

```
call_me_maybe/
├── data/
│   ├── input/
│   │   ├── function_calling_tests.json
│   │   └── functions_definition.json
│   └── output/
│       └── function_calling_results.json
├── src/
│   ├── __init__.py
│   └── main.py
├── llm_sdk/
│   └── ...
├── Makefile
├── pyproject.toml
└── README.md
```

## 🔧 Implementation Details

### Input Files

#### 1. `function_calling_tests.json`

Contains natural language prompts to process:

```json
[
  {
    "prompt": "What is the sum of 2 and 3?"
  },
  {
    "prompt": "Greet shrek"
  },
  {
    "prompt": "Reverse the string 'hello'"
  }
]
```

#### 2. `functions_definition.json`

Defines available functions with their schemas:

```json
[
  {
    "name": "fn_add_numbers",
    "description": "Add two numbers together and return their sum.",
    "parameters": {
      "a": {
        "type": "number"
      },
      "b": {
        "type": "number"
      }
    },
    "returns": {
      "type": "number"
    }
  },
  {
    "name": "fn_greet",
    "description": "Generate a greeting message for a person by name.",
    "parameters": {
      "name": {
        "type": "string"
      }
    },
    "returns": {
      "type": "string"
    }
  }
]
```

> ⚠️ **Note**: Input files may change during testing. Do not hardcode solutions based on examples.

## 📤 Output Format

### Output File: `function_calling_results.json`

Each object must contain exactly:

- **prompt** (string): Original natural-language request
- **name** (string): Function name to call
- **parameters** (object): Required arguments with correct types

### Example Output

```json
[
  {
    "prompt": "What is the sum of 2 and 3?",
    "name": "fn_add_numbers",
    "parameters": {"a": 2.0, "b": 3.0}
  },
  {
    "prompt": "Reverse the string 'hello'",
    "name": "fn_reverse_string",
    "parameters": {"s": "hello"}
  }
]
```

### Validation Rules

✅ Valid JSON (no trailing commas, no comments)  
✅ Keys and types must match schema exactly  
✅ No extra keys or prose  
✅ All required arguments present  
✅ Correct argument types (number, string, boolean, etc.)  

## 🤖 LLM Interaction

### The LLM SDK

The `Small_LLM_Model` class provides:

#### Methods

- **`get_logits_from_input_ids(input_ids: Tensor) -> Tensor`**  
  Returns raw logits from input token IDs

- **`get_path_to_vocabulary_json() -> str`**  
  Returns path to JSON file mapping token IDs to tokens

- **`encode(text: str) -> List[int]`**  
  Encodes text into token IDs

- **`decode(token_ids: List[int]) -> str`** *(optional)*  
  Decodes token IDs back to text

### Generation Pipeline

1. **Prompt**: Natural language question
2. **Tokenization**: Text → subword tokens
3. **Input IDs**: Tokens → numerical IDs
4. **LLM Processing**: Neural network processes IDs
5. **Logits**: Probability scores for next token
6. **Token Selection**: Choose next token (with constraints)

This process repeats token-by-token until completion.

### Constrained Decoding

**Key Concept**: Modify logits before token selection to enforce valid JSON structure and schema compliance.

#### Process

1. Model produces logits for all possible tokens
2. Identify tokens that maintain valid JSON and schema
3. Set invalid token logits to negative infinity
4. Sample only from valid tokens

#### Critical Points

⚠️ **Do NOT** rely on the model spontaneously producing correct JSON from prompts alone  
✅ **DO** use vocabulary JSON to map tokens to strings  
✅ **DO** enforce both structural and semantic validity  
✅ **DO** guarantee 100% parseable JSON output  

> 💡 **Tip**: Use the vocabulary JSON file to determine which tokens are valid at each generation step.

## 🧪 Testing

### Verification Steps

1. Ensure input files are in `data/input/`
2. Run the program:
   ```bash
   uv run python -m src
   ```
3. Check that `output/function_calling_results.json` is created
4. Validate JSON structure and content
5. Verify function names and argument types match definitions

### Edge Cases to Test

- Empty strings
- Large numbers
- Special characters
- Wrong types
- Ambiguous prompts
- Functions with multiple parameters
- Malformed input JSON
- Missing files
- Invalid function definitions

### Error Handling

Your implementation must:

- ✅ Handle malformed JSON inputs gracefully
- ✅ Handle missing files
- ✅ Provide clear error messages
- ✅ Never crash unexpectedly

## 📊 Performance Requirements

### Accuracy

- **Function Selection**: 90%+ correct
- **Argument Extraction**: 90%+ correct
- **JSON Validity**: 100% (every output must be parseable and schema-compliant)

### Speed

- Process all test prompts in **under 5 minutes** on standard hardware

### Reliability

- Robust error handling for all edge cases
- Graceful degradation on invalid inputs

> 💪 **Power of Constrained Decoding**: The Qwen3-0.6B model has only 500 million parameters, yet with proper constrained decoding, it achieves reliability comparable to much larger models.

## 📝 Notes

- The reviewer will run `uv sync` to set up the environment
- Do not hardcode solutions based on provided examples
- Input files may change during peer review
- Focus on structural guidance over raw model capabilities

## 🤝 Contributing

This project is part of an educational assignment. Please follow the requirements and constraints outlined above.

## 📄 License

[Specify your license here]

---

**Project**: Call Me Maybe - Introduction to Function Calling in LLMs
