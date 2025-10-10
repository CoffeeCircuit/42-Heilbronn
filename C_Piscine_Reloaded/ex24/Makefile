# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 10:38:29 by abalcu            #+#    #+#              #
#    Updated: 2025/10/10 10:40:31 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = 		libft.a
INCLUDE = 	includes
CFILES =	srcs/ft_putchar.c	\
			srcs/ft_putstr.c	\
			srcs/ft_strcmp.c	\
			srcs/ft_strlen.c	\
			srcs/ft_swap.c

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
