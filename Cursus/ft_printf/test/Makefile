
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = test

CFILES = 	ft_test.c ft_test_digits.c ft_test_hex.c ft_test_pointer.c \
			ft_test_unsigned.c ft_test_char.c ft_test_percent.c \
			ft_test_string.c

OFILES = $(CFILES:.c=.o)

.PHONY: all re fclean clean

all:$(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

re:fclean all

fclean:clean
	rm -f $(NAME)

clean:
	rm -f $(OFILES)
