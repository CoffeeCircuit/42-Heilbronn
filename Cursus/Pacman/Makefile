.PHONY: install run debug clean lint lint-strict test re

PY_FILES := pac-man.py 

GREEN := \033[0;32mOK\033[0m
RED := \033[0;31mKO\033[0m


install:
	UV_SKIP_WHEEL_FILENAME_CHECK=1 uv sync --python 3.10

# use this to create the WebAssembly for itch.io
build:
	UV_SKIP_WHEEL_FILENAME_CHECK=1 uv run pygbag --disable-sound-format-error --no_opt pac-man.py

run:
	uv run pac-man.py $(ARGS)

debug:
	uv run python3 -m pdb pac-man.py $(ARGS)

clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	find . -type d -name .mypy_cache -exec rm -rf {} +
	find . -type d -name .venv -exec rm -rf {} +
	find . -type d -name build -exec rm -rf {} +
	find . -type d -name dist -exec rm -rf {} +
	find . -name .pytest_cache -exec rm -rf {} +
	find . -name .ruff_cache -exec rm -rf {} +
	find . -name "*.pyc" -delete
	find . -name "*.pyo" -delete

# use this target to run the unit tests
test:
	pytest test -vv
	@echo "WHEN PROJECT IF FINISHED REMOVE THE TEST FOLDER"

lint:
	UV_SKIP_WHEEL_FILENAME_CHECK=1 uv run flake8 $(PY_FILES)
	UV_SKIP_WHEEL_FILENAME_CHECK=1 uv run mypy $(PY_FILES) \
		--explicit-package-bases \
		--warn-return-any \
		--warn-unused-ignores \
		--ignore-missing-imports \
		--disallow-untyped-defs \
		--check-untyped-defs \
		--exclude '(^\.venv/)'

lint-strict:
	UV_SKIP_WHEEL_FILENAME_CHECK=1 uv run flake8 $(PY_FILES)
	UV_SKIP_WHEEL_FILENAME_CHECK=1 uv run mypy $(PY_FILES)\
		--explicit-package-bases \
		--strict \
		--exclude '(^\.venv/)'

re: clean install
