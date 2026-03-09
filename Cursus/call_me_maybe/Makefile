.PHONY: install run debug clean lint lint-strict benchmark


install:
	uv sync --no-cache --link-mode=copy --python 3.10
	uv pip install --no-cache --link-mode=copy -e ./llm_sdk

run:
	uv run -m src

debug:
	uv run -m pdb src $(ARGS)

clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	find . -type d -name .mypy_cache -exec rm -rf {} +
	find . -type d -name .venv -exec rm -rf {} +
	find . -type d -name dist -exec rm -rf {} +
	find . -type d -name HF -exec rm -rf {} +
	find . -name .pytest_cache -exec rm -rf {} +
	find . -name .ruff_cache -exec rm -rf {} +
	find . -name "*.pyc" -delete
	find . -name "*.pyo" -delete
	uv cache clean

lint:
	uv run flake8 src/
	uv run mypy src/ \
		--warn-return-any \
		--warn-unused-ignores \
		--ignore-missing-imports \
		--disallow-untyped-defs \
		--check-untyped-defs \
		--exclude '(^\.venv/)' \
		--exclude '(^\.llm_sdk/)'

lint-strict:
	uv run flake8 src/
	uv run mypy src/ \
		--strict \
		--exclude '(^\.venv/)' \
		--exclude '(^\.llm_sdk/)'

