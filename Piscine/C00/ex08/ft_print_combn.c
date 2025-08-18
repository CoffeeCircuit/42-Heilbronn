/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 06:42:14 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/04 10:41:19 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_increment(char *str, int cur_pos, int size)
{
	int	offset;

	offset = size - cur_pos - 1;
	str = str + offset;
	if (*str >= '9' - cur_pos)
		ft_increment(str - offset, cur_pos + 1, size);
	else
	{
		(*str)++;
		str++;
		while (*str)
		{
			(*str) = *(str - 1) + 1;
			str++;
		}
		str = str - size;
	}
}

void	ft_init(char *buf, int n)
{
	int	index;

	index = 0;
	while (index < 10)
	{
		buf[index] = '0' + index;
		index++;
	}
	buf[n] = '\0';
}

void	ft_print_combn(int n)
{
	char	buf[10];

	ft_init(buf, n);
	while (buf[0] <= '9' - n)
	{
		write(1, buf, n);
		write(1, ", ", 2);
		ft_increment(buf, 0, n);
		if (buf[0] > '9' - (n))
		{
			write(1, buf, n);
			break ;
		}
	}
}
