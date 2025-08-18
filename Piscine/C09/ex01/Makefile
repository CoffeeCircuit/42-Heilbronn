# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 08:33:58 by abalcu            #+#    #+#              #
#    Updated: 2025/08/18 15:56:19 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = 		libft.a
INCLUDE = 	includes
CFILES =	srcs/ft_putchar.c	\
			srcs/ft_swap.c		\
			srcs/ft_putstr.c	\
			srcs/ft_strlen.c	\
			srcs/ft_strcmp.c

OFILES = $(CFILES:.c=.o)

all:$(NAME)

$(NAME):$(OFILES)
	ar rcs $(NAME) $(OFILES)

%.o:%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

re:fclean all

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
