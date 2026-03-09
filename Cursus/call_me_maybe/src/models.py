from pydantic import BaseModel, Field
from typing import Any


class FunctionDefinition(BaseModel):
    """Schema for a function definition."""

    name: str
    description: str
    parameters: dict[str, dict[str, Any]]
    returns: dict[str, Any]


class TestCase(BaseModel):
    """Schema for input test case."""

    prompt: str


class FunctionCall(BaseModel):
    """Schema for output function call."""

    prompt: str
    name: str
    parameters: dict[str, Any] = Field(default_factory=dict)


class Config(BaseModel):
    """CLI configuration."""

    functions_definition: str = "data/input/functions_definition.json"
    input: str = "data/input/function_calling_tests.json"
    output: str = "data/output/function_calling_results.json"
