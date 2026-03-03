.PHONY: install run debug clean lint lint-strict

install:
	uv sync --python 3.10

run:
	uv run python3 flyin.py $(ARGS)

debug:
	uv run python3 -m pdb flyin.py $(ARGS)

clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	find . -type d -name .mypy_cache -exec rm -rf {} +
	find . -name .pytest_cache -exec rm -rf {} +
	find . -name .ruff_cache -exec rm -rf {} +
	find . -name "*.pyc" -delete
	find . -name "*.pyo" -delete

lint:
	uv run flake8 *.py
	uv run mypy *.py\
		--warn-return-any \
		--warn-unused-ignores \
		--ignore-missing-imports \
		--disallow-untyped-defs \
		--check-untyped-defs \
		--exclude '(^\.venv/)'

lint-strict:
	uv run flake8 *.py
	uv run mypy *.py\
		--strict \
		--exclude '(^\.venv/)'
