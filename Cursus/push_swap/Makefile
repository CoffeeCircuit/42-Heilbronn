# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 22:36:09 by abalcu            #+#    #+#              #
#    Updated: 2025/11/25 03:51:04 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

NAME = 		push_swap
CFILES = 	ft_atoi.c ft_calloc.c ft_memmove.c ft_split.c ft_memcpy.c \
			ft_memset.c ft_isdigit.c ft_putstr_fd.c parser.c push_swap.c \
			ft_strlen.c sort.c utils.c utils_ops1.c utils_ops2.c utils_ops3.c \
			utils_parser.c utils_sort.c

OFILES = $(CFILES:.c=.o)

all:$(NAME)

$(NAME):$(OFILES)
	$(CC) $(OFILES) -o $(NAME)

$(OBONUSFILES):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

re:fclean all

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
