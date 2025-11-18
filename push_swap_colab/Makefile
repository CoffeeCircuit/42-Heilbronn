# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/07 15:12:42 by mawelsch          #+#    #+#              #
#    Updated: 2025/11/18 11:28:37 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -g #-Wall -Wextra -Werror

NAME = push_swap

CFILES = 	push_swap.c sort_adaptive.c sort.c sort_complex.c sort_medium.c \
			sort_simple.c utils_bench.c utils.c utils_ops1.c utils_ops2.c \
			utils_ops3.c utils_parser.c utils_arg_str.c utils_medium_sort.c \
			merge_utils_a.c merge_utils_b.c list_size_utils.c 

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
