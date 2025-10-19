# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/08 08:25:57 by abalcu            #+#    #+#              #
#    Updated: 2025/10/19 11:02:15 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		libftprintf.a
SRCD = 		src/
INCLUDED = 	include/
LIBD =		lib/
LIB =		libft.a

CFILES = 	$(SRCD)ft_parse.c \
			ft_printf.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -I$(INCLUDED) -L$(LIBD) -l$(subst lib,,$(basename $(LIB)))

OFILES = $(CFILES:.c=.o)

.PHONY: all re fclean clean

all:$(NAME)

$(NAME): $(OFILES)
	@cp $(LIBD)$(LIB) $@
	ar -rs $@ $(OFILES)

$(SRCD)%.o: $(SRCD)%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

re:fclean all

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
