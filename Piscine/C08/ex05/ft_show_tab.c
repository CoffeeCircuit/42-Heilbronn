/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 18:56:23 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/19 13:22:56 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <unistd.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void	ft_putnbr(int nb)
{
	int		index;
	char	temp_char;
	char	buf[12];

	index = 0;
	if (nb < 0)
		write(1, "-", 1);
	while (index < 12)
	{
		if (nb < 0)
			temp_char = '0' - nb % 10;
		else if (nb == 0 && index == 0)
			temp_char = '0' + nb % 10;
		else if (nb > 0)
			temp_char = '0' + nb % 10;
		else
			temp_char = '\0';
		buf[index] = temp_char;
		index++;
		nb /= 10;
	}
	while (index--)
		if (buf[index] != '\0')
			write(1, buf + index, 1);
}

void	ft_show_tab(struct s_stock_str *par)
{
	int	index;

	index = 0;
	while (par[index].str)
	{
		write(1, par[index].str, ft_strlen(par[index].str));
		write(1, "\n", 1);
		ft_putnbr(par[index].size);
		write(1, "\n", 1);
		write(1, par[index].copy, ft_strlen(par[index].copy));
		write(1, "\n", 1);
		index++;
	}
}
