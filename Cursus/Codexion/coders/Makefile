# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 23:38:12 by abalcu            #+#    #+#              #
#    Updated: 2026/02/15 11:27:55 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	codexion
SRCS =	argparse.c coders_debug.c coders_refactor.c dongles.c logging.c \
		sim_init.c coders.c coders_init.c codexion.c dongles_init.c \
		monitoring.c scheduler.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pthread -std=c89
CFLAGS_ASAN = $(CFLAGS) -fsanitize=address -fsanitize=leak
LDFLAGS =

.PHONY: all clean fclean re asan test show_compilation_sequence

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

asan: $(OBJS)
	$(CC) $(CFLAGS_ASAN) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	@echo Tesing \(50x\) \'./codexion 10 350 100 100 100 5 10\'
	@bash -c 'for i in {1..50}; do \
		echo -n "Run $$i: "; \
		timeout 5 ./codexion 10 350 100 100 100 5 10 edf 2>&1 \
			| tail -1 || echo "timeout"; \
		done'

show_compilation_sequence: $(NAME)
	@echo Shows order in which 10 coders are compiling with 3 requiered runs
	@echo -n "fifo: "; \
	./codexion 10 350 100 100 100 3 10 fifo 2>&1 \
		| awk '$$4 == "compiling"{printf "%2d ", $$2}'; echo
	@echo -n "edf : "; \
	./codexion 10 350 100 100 100 3 10 edf 2>&1 \
		| awk '$$4 == "compiling"{printf "%2d ", $$2}'; echo
