from enum import Enum, auto
from typing import Set
from pydantic import BaseModel, Field


class JSONState(Enum):
    """States for JSON parsing during constrained generation."""

    EMPTY = auto()  # Initial state
    LIST_START = auto()  # After [
    OBJ_START = auto()  # After {
    EXPECT_KEY = auto()  # Waiting for key string
    EXPECT_SEP = auto()  # After key, waiting for :
    EXPECT_VALUE = auto()  # After :, waiting for value
    AFTER_VALUE = auto()  # After value, waiting for , or }
    OBJ_END = auto()  # After }
    LIST_END = auto()  # After ]


class JSONStateMachine(BaseModel):
    """Finite state machine for JSON structure validation."""

    state: JSONState = JSONState.EMPTY
    current_key: str = Field(default="")
    current_string: str = Field(default="")
    in_string: bool = False
    depth: int = 0
    building_value: bool = False  # Track if we're building a non-string value
    value_chars_count: int = 0  # Count characters in current value

    def get_next_valid_tokens(self, vocab: Set[str]) -> Set[str]:
        """
        Get structurally valid tokens based on current FSM state.

        Args:
            vocab: Set of all vocabulary tokens

        Returns:
            Set of tokens that maintain JSON structural validity
        """
        match self.state:
            case JSONState.EMPTY:
                return {"["}

            case JSONState.LIST_START:
                # After [, expect whitespace or {
                return {"{", " ", "\n", "\t"} & vocab

            case JSONState.OBJ_START:
                # After {, expect whitespace or opening quote for key
                return {" ", '"', "\n", "\t"} & vocab

            case JSONState.EXPECT_KEY:
                if not self.in_string:
                    # Need to start key string OR close empty object
                    return {'"', "}"} & vocab
                else:
                    # Inside key string - allow all tokens
                    # The schema validator will constrain to valid key names
                    return vocab

            case JSONState.EXPECT_SEP:
                # After key, expect : or whitespace
                return {":", " ", "\n", "\t"} & vocab

            case JSONState.EXPECT_VALUE:
                if not self.in_string:
                    if self.building_value and self.value_chars_count > 0:
                        # Already building a value, restrict to continuation or delimiter
                        valid = {",", "}", " ", "\n", "\t"} & vocab
                        # Allow limited continuation for numbers (max 10 chars)
                        if self.value_chars_count < 10:
                            valid.update(
                                {
                                    "0",
                                    "1",
                                    "2",
                                    "3",
                                    "4",
                                    "5",
                                    "6",
                                    "7",
                                    "8",
                                    "9",
                                }
                                & vocab
                            )
                            # Allow decimal point only if not already present
                            if self.value_chars_count < 5:
                                valid.update({"."} & vocab)
                        return valid
                    # Starting a new value
                    # Can start string, number, boolean, object, or array
                    valid = {'"', "{", "[", " ", "\n", "\t"} & vocab
                    # Allow digits and boolean literals
                    valid.update(
                        {
                            "true",
                            "false",
                            "t",
                            "f",
                            "tr",
                            "tru",
                            "fa",
                            "fal",
                            "fals",
                        }
                        & vocab
                    )
                    # Allow digits, decimal point, minus for numbers
                    valid.update(
                        {
                            "0",
                            "1",
                            "2",
                            "3",
                            "4",
                            "5",
                            "6",
                            "7",
                            "8",
                            "9",
                            "-",
                            ".",
                        }
                        & vocab
                    )
                    return valid
                else:
                    # Inside value string - allow ALL tokens
                    # (schema will filter)
                    return vocab

            case JSONState.AFTER_VALUE:
                # After value, expect , or } or whitespace
                valid = {",", "}", " ", "\n", "\t"} & vocab
                return valid

            case JSONState.OBJ_END:
                # After }, if we're at depth 0, we're done - no more tokens
                if self.depth == 0:
                    return set()
                # Otherwise allow ] to close outer array or whitespace
                return {"]", " ", "\n", "\t"} & vocab

            case JSONState.LIST_END:
                # Final state - no more tokens
                return set()

        return set()

    def update_state(self, token: str) -> None:
        """
        Update FSM state after consuming a token.

        Args:
            token: The token that was just generated
        """
        # Handle string delimiters
        if token == '"':
            if self.in_string:
                # Closing quote
                self.in_string = False

                if self.state == JSONState.EXPECT_KEY:
                    # Just finished key
                    self.current_key = self.current_string
                    self.current_string = ""
                    self.state = JSONState.EXPECT_SEP
                elif self.state == JSONState.EXPECT_VALUE:
                    # Just finished value
                    self.current_string = ""
                    self.state = JSONState.AFTER_VALUE
            else:
                # Opening quote
                self.in_string = True
                self.current_string = ""
                # Transition OBJ_START to EXPECT_KEY when opening quote appears
                if self.state == JSONState.OBJ_START:
                    self.state = JSONState.EXPECT_KEY
            return

        if self.in_string:
            self.current_string += token
            return

        # Handle structural tokens (not in string)
        if token == "[":
            self.state = JSONState.LIST_START
        elif token == "{":
            self.depth += 1
            self.state = JSONState.EXPECT_KEY
        elif token == ":":
            self.state = JSONState.EXPECT_VALUE
        elif token == ",":
            if (
                self.state == JSONState.AFTER_VALUE
                or self.state == JSONState.EXPECT_VALUE
            ):
                # Transition to next key
                self.state = JSONState.EXPECT_KEY
                self.current_key = ""
        elif token == "}":
            # Closing brace - transition from EXPECT_VALUE or AFTER_VALUE
            if self.state == JSONState.EXPECT_VALUE:
                # Empty value, just close
                pass
            self.building_value = False
            self.value_chars_count = 0
            self.depth -= 1
            if self.depth > 0:
                # Closed a nested object, now waiting for comma or another close
                self.state = JSONState.AFTER_VALUE
            else:
                # Closed the main object
                self.state = JSONState.OBJ_END
        elif token == "]":
            self.state = JSONState.LIST_END
        elif token in {" ", "\n", "\t"}:
            # Whitespace doesn't change state
            # But it ends value building
            if self.state == JSONState.EXPECT_VALUE and self.building_value:
                self.state = JSONState.AFTER_VALUE
                self.building_value = False
                self.value_chars_count = 0
        else:
            # For any other characters (digits, letters in numbers/booleans),
            # we're building up the value
            if self.state == JSONState.EXPECT_VALUE and not self.in_string:
                self.building_value = True
                self.value_chars_count += 1
