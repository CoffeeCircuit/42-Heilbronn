# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/07 15:12:42 by mawelsch          #+#    #+#              #
#    Updated: 2025/11/18 05:47:31 by mawelsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g #-Wall -Wextra -Werror

NAME = push_swap

CFILES = 	push_swap.c sort_adaptive.c sort.c sort_complex.c sort_medium.c \
			sort_simple.c utils_bench.c utils.c utils_ops1.c utils_ops2.c \
			utils_ops3.c utils_parser.c utils_arg_str.c merge_utils_a.c \
			merge_utils_b.c list_size_utils.c

OFILES = $(CFILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME) clean

$(NAME): $(OFILES)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) -L./libft -lft

clean:
	rm -f $(OFILES) $(LIBFT_OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
