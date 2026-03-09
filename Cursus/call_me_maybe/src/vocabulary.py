from typing import Set
import json


class VocabularyHandler:
    """
    Manages vocabulary with efficient token matching
    (non-pydantic for speed).
    """

    def __init__(self, token_to_id: dict, id_to_token: dict):
        self.token_to_id = token_to_id
        self.id_to_token = id_to_token

    @classmethod
    def read(cls, path: str) -> "VocabularyHandler":
        print("   Loading vocab file...")
        with open(path) as fp:
            vocab = json.load(fp)
        print(f"   Creating reverse mapping for {len(vocab)} tokens...")
        id_to_token = {v: k for k, v in vocab.items()}
        print("   Initializing handler...")
        return cls(token_to_id=vocab, id_to_token=id_to_token)

    def get_next_valid_tokens(
        self, current_txt: str, valid_completions: Set[str]
    ) -> Set[int]:
        """
        Get the next valid token ID's from the current string
        """

        next_valid_tokens = set()

        for completion in valid_completions:
            if not completion.startswith(current_txt):
                continue

            remaining_str = completion[len(current_txt):]
            if not remaining_str:
                continue

            for token_str, token_id in self.token_to_id.items():
                if remaining_str.startswith(token_str):
                    next_valid_tokens.add(token_id)

        return next_valid_tokens
