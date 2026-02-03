# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/26 23:38:12 by abalcu            #+#    #+#              #
#    Updated: 2026/02/03 23:05:59 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
SRCS = 	argparse.c codexion.c destructors.c init_coders.c init_dongles.c \
		init_queue.c init_steps.c job_coder.c job_monitor.c logging_actions.c \
		logging.c scheduler.c timing.c job_coder_utils.c
OBJS = $(SRCS:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
LDFLAGS =


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

