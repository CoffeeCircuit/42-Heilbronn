import numpy as np
from typing import Set
from pydantic import BaseModel
from src.fsm import JSONStateMachine, JSONState
from src.schema import SchemaValidator
from src.vocabulary import VocabularyHandler


class ConstrainedDecoder(BaseModel):
    """Combines FSM and schema validation for constrained decoding."""

    fsm: JSONStateMachine
    schema_validator: SchemaValidator
    vocab: VocabularyHandler
    current_value: str = ""
    _all_tokens_cache: Set[str] | None = None

    class Config:
        arbitrary_types_allowed = True

    def model_post_init(self, __context) -> None:
        """Initialize after model creation."""
        # Cache all tokens
        if self._all_tokens_cache is None:
            self._all_tokens_cache = set(self.vocab.token_to_id.keys())

    def get_valid_token_ids(self) -> Set[int]:
        """
        Combine FSM (structure) and schema (semantics) constraints.

        Returns set of token IDs that satisfy BOTH:
        1. JSON structural validity (FSM)
        2. Schema semantic validity
        """
        # Layer 1: FSM filters for structural validity
        assert self._all_tokens_cache is not None

        try:
            structurally_valid = self.fsm.get_next_valid_tokens(
                self._all_tokens_cache
            )
        except Exception as e:
            print(f"\n[ERROR in FSM: {e}]", flush=True)
            return set()

        # Layer 2: Schema filters for semantic validity
        from src.fsm import JSONState

        try:
            semantically_valid = (
                self.schema_validator.get_valid_tokens_semantic(
                    current_key=self.fsm.current_key,
                    current_value=self._get_current_value(),
                    vocab_tokens=structurally_valid,
                    in_string=self.fsm.in_string,
                    is_expecting_key=(self.fsm.state == JSONState.EXPECT_KEY),
                    is_expecting_value=(
                        self.fsm.state == JSONState.EXPECT_VALUE
                    ),
                    depth=self.fsm.depth,
                )
            )
        except Exception as e:
            print(f"\n[ERROR in schema validator: {e}]", flush=True)
            return set()

        # Convert tokens to IDs
        return {
            self.vocab.token_to_id[token]
            for token in semantically_valid
            if token in self.vocab.token_to_id
        }

    def mask_logits(self, logits: np.ndarray) -> np.ndarray:
        """Apply combined FSM + schema constraints to logits."""
        valid_token_ids = self.get_valid_token_ids()

        masked_logits = np.full_like(logits, -np.inf)
        for token_id in valid_token_ids:
            masked_logits[token_id] = logits[token_id]

        return masked_logits

    def update_after_token(self, token: str) -> None:
        """Update decoder state after consuming a token."""
        # Multi-character tokens need to be processed character by character
        # for the FSM to work correctly
        for char in token:
            # Check BEFORE updating FSM state
            was_in_string = self.fsm.in_string
            old_state = self.fsm.state
            old_depth = self.fsm.depth

            self.fsm.update_state(char)

            # Track when we complete a top-level key
            # (just closed a key string at depth 1)
            if (
                char == '"'
                and was_in_string
                and old_depth == 1
                and old_state == JSONState.EXPECT_KEY
                and self.fsm.current_key  # Use AFTER update
            ):
                # We just completed a top-level key
                self.schema_validator.mark_key_complete(self.fsm.current_key)

            # Track when we complete a parameter key (depth 2)
            if (
                char == '"'
                and was_in_string
                and old_depth == 2
                and old_state == JSONState.EXPECT_KEY
                and self.fsm.current_key  # Use AFTER update
                and self.schema_validator.current_function_name
            ):
                # We just completed a parameter key
                self.schema_validator.mark_parameter_complete(
                    self.fsm.current_key
                )

            # Track when we complete the function name value
            if (
                char == '"'
                and was_in_string
                and old_depth == 1
                and self.fsm.current_key == "name"  # Use AFTER update
                and old_state == JSONState.EXPECT_VALUE
                and self.current_value
            ):
                # We just closed the function name value
                self.schema_validator.set_function_name(self.current_value)

            # Track value being built when inside a string
            # Don't include the opening/closing quotes themselves
            if char == '"':
                # Reset when we see a quote (either opening or closing)
                self.current_value = ""
            elif self.fsm.in_string:
                # Only add non-quote characters to the value
                self.current_value += char

    def _get_current_value(self) -> str:
        """Track partially generated value (implementation detail)."""
        return self.current_value
