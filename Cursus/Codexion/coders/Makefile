# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 23:38:12 by abalcu            #+#    #+#              #
#    Updated: 2026/02/13 08:39:49 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	codexion
SRCS =	argparse.c coders_debug.c coders_refactor.c dongles.c logging.c \
		sim_init.c coders.c coders_init.c codexion.c dongles_init.c \
		monitoring.c cooldown.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -pthread -std=c89
CFLAGS_ASAN = $(CFLAGS) -fsanitize=address -fsanitize=leak
LDFLAGS =

.PHONY: all clean fclean re asan

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

