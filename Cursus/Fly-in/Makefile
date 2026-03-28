.PHONY: install run debug clean lint lint-strict benchmark

PY_FILES := colors.py config.py flyin.py graph.py parser.py \
			scheduler.py simulation.py visualizer.py

OK := \033[0;32mOK\033[0m
KO := \033[0;31mKO\033[0m


install:
	uv sync --python 3.10

run:
	uv run python3 flyin.py $(ARGS)

debug:
	uv run python3 -m pdb flyin.py $(ARGS)

clean:
	find . -type d -name __pycache__ -exec rm -rf {} +
	find . -type d -name .mypy_cache -exec rm -rf {} +
	find . -type d -name .venv -exec rm -rf {} +
	find . -name .pytest_cache -exec rm -rf {} +
	find . -name .ruff_cache -exec rm -rf {} +
	find . -name "*.pyc" -delete
	find . -name "*.pyo" -delete

lint:
	uv run --no-project flake8 $(PY_FILES)
	uv run --no-project mypy $(PY_FILES) \
		--explicit-package-bases \
		--warn-return-any \
		--warn-unused-ignores \
		--ignore-missing-imports \
		--disallow-untyped-defs \
		--check-untyped-defs \
		--exclude '(^\.venv/)'

lint-strict:
	uv run --no-project flake8 $(PY_FILES)
	uv run --no-project mypy $(PY_FILES)\
		--explicit-package-bases \
		--strict \
		--exclude '(^\.venv/)'

benchmark:
	@echo "========================================"
	@echo "Running Fly-in Performance Benchmarks"
	@echo "========================================"
	@echo ""
	@check_result() { \
		target=$$1; \
		if [ $$steps -le $$target ]; then \
			echo "≤$$target $(OK)"; \
			passed=$$((passed + 1)); \
		else \
			echo "≤$$target $(KO) (exceeded by $$((steps - target)))"; \
			failed=$$((failed + 1)); \
		fi; \
	}; \
	total=0; passed=0; failed=0; \
	for py_path in $$(find ./maps -type f -iname '*.txt' | sort); do \
		py_file=$$(basename "$$py_path"); \
		difficulty=$$(dirname "$$py_path" | xargs basename); \
		echo "Testing: $$py_file [$$difficulty]"; \
		steps=$$(uv run python3 flyin.py "$$py_path" | wc -l); \
		printf "  Result: $$steps steps | Target: "; \
		total=$$((total + 1)); \
		case $$py_file in \
			01_linear_path.txt) check_result 6 ;; \
			02_simple_fork.txt) check_result 6 ;; \
			03_basic_capacity.txt) check_result 8 ;; \
			01_dead_end_trap.txt) check_result 15 ;; \
			02_circular_loop.txt) check_result 20 ;; \
			03_priority_puzzle.txt) check_result 12 ;; \
			01_maze_nightmare.txt) check_result 45 ;; \
			02_capacity_hell.txt) check_result 60 ;; \
			03_ultimate_challenge.txt) check_result 35 ;; \
			01_the_impossible_dream.txt) check_result 45 ;; \
		esac; \
		echo ""; \
	done; \
	echo "========================================"; \
	echo "Benchmark Summary"; \
	echo "========================================"; \
	echo "Total tests: $$total"; \
	echo "Passed: $$passed $(OK)"; \
	echo "Failed: $$failed $(KO)"; \
	if [ $$failed -eq 0 ]; then \
		echo ""; \
		echo "🎉 All benchmarks passed!"; \
	fi
