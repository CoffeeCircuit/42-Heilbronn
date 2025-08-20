# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 18:36:29 by abalcu            #+#    #+#              #
#    Updated: 2025/08/20 16:09:46 by abalcu           ###   ########.fr        #
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

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
