# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 23:38:12 by abalcu            #+#    #+#              #
#    Updated: 2026/01/27 04:39:53 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=codexion
SRCS = codexion.c argparse.c
OBJS = $(SRCS:.c=.o)
INCLUDES = coders/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
LDFLAGS =


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

