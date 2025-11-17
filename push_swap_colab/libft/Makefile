# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 13:27:03 by mawelsch          #+#    #+#              #
#    Updated: 2025/11/12 05:18:24 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -fPIE

NAME = libft.a

CFILES = ft_bzero.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
ft_tolower.c ft_isalnum.c ft_isprint.c ft_memset.c ft_strlen.c \
ft_toupper.c ft_isalpha.c ft_memchr.c ft_strchr.c ft_strncmp.c \
ft_isascii.c ft_memcpy.c ft_strlcat.c ft_strrch.c ft_memcmp.c \
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c \
ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
ft_ltoa.c ft_uitoa.c ft_hex_flags.c ft_non-hex_flags.c ft_printf.c \
get_next_line.c

OFILES = $(CFILES:.c=.o)


.PHONY: all clean fclean re bonus bonuslib

all: $(NAME) clean

$(NAME) : $(OFILES)
	@ar rcs $(NAME) $(OFILES)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all


