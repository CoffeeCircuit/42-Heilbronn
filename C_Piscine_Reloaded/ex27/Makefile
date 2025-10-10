# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/07 16:06:58 by abalcu            #+#    #+#              #
#    Updated: 2025/10/07 16:10:23 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = 		ft_display_file
CFILES =	ft_display_file.c

OFILES = $(CFILES:.c=.o)

all:$(NAME)

$(NAME):$(OFILES)
	$(CC) $(OFILES) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

re:fclean all

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
