# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_creator.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 14:03:29 by abalcu            #+#    #+#              #
#    Updated: 2025/08/18 14:06:43 by abalcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

gcc -Wall -Werror -Wextra -c ft_putchar.c -o ft_putchar.o
gcc -Wall -Werror -Wextra -c ft_swap.c -o ft_swap.o
gcc -Wall -Werror -Wextra -c ft_putstr.c -o ft_putstr.o
gcc -Wall -Werror -Wextra -c ft_strlen.c -o ft_strlen.o
gcc -Wall -Werror -Wextra -c ft_strcmp.c -o ft_strcmp.o
ar rcs libft.a *.o
rm *.o
