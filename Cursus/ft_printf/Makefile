# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 08:25:57 by abalcu            #+#    #+#              #
#    Updated: 2025/11/01 18:25:17 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		libftprintf.a
SRCD = 		src/

CFILES = 	$(SRCD)ft_format.c $(SRCD)ft_parse.c $(SRCD)ft_utils.c \
			$(SRCD)ft_writes2.c $(SRCD)ft_writes.c  $(SRCD)ft_isdigit.c \
			$(SRCD)ft_strchr.c $(SRCD)ft_strlen.c $(SRCD)ft_untils_int.c\
			ft_printf.c

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

OFILES = $(CFILES:.c=.o)

.PHONY: all re fclean clean

all:$(NAME)

bonus:$(NAME)

$(NAME): $(OFILES)
	ar -rcs $@ $(OFILES)

$(SRCD)%.o: $(SRCD)%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

re:fclean all

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
