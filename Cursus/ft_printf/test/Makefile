SHELL = /bin/bash

# Format strings to test
FORMATS = "%d" "%+d" "% d" "%05d" "%-5d" "%+05d" "%-+5d" \
	"%x" "%#x" "%05x" "%-5x" "%#05x" \
	"%f" "%+f" "% f" "%05.2f" "%-5.2f" "%+05.2f" \
	"%o" "%#o" "%05o" "%-5o" "%#05o" \
	"%c" "%-5c" \
	"%s" "%-10s"

# Matching arguments for each format
ARGS = "42" "42" "42" "42" "42" "42" "42" \
	"255" "255" "255" "255" "255" \
	"3.14" "3.14" "3.14" "3.14" "3.14" "3.14" \
	"10" "10" "10" "10" "10" \
	"'A'" "'A'" \
	"\"Hi\"" "\"Hi\""

OK = "[ \033[0;32mOK\033[0m ]"
KO = "[ \033[0;31mKO\033[0m ]"

all: test run

test:
	@cc -g ft_test.c -o test

run:
	@formats=($(FORMATS)); \
	args=($(ARGS)); \
	for i in $${!formats[@]}; do \
		fmt=$${formats[$$i]}; \
		arg=$${args[$$i]}; \
		echo -n $$'\t'; \
		echo ft_printf\(\"$$fmt\", $$arg\); \
		echo -n $$'\tGot: "'; ./test "$$fmt" $$arg; echo -n '", '; \
		echo -n 'Expected: "'; printf "$$fmt" $$arg; echo '"'; \
		echo ; \
	done
