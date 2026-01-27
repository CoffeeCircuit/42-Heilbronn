# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 23:38:12 by abalcu            #+#    #+#              #
#    Updated: 2026/01/26 23:38:15 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=codexion
SRCS = codexion.c
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
	@echo "Cleaning object files..."
	rm -f $(OBJS)

fclean: clean
	@echo "Cleaning up binary files..."
	rm -f $(NAME)

re: fclean all
	@echo "Rebuilding everything."

