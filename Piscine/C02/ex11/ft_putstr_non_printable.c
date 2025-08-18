/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:35:05 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 14:25:21 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	index;

	index = 0;
	while (index < n && src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	while (index < n)
	{
		dest[index] = '\0';
		index++;
	}
	return (dest);
}

void	ft_print_hex(char chr)
{
	char	hex_symbols[16];

	ft_strncpy(hex_symbols, "0123456789abcdef", 17);
	write(1, "\\", 1);
	write(1, &hex_symbols[chr / 16], 1);
	write(1, &hex_symbols[chr % 16], 1);
}

void	ft_putstr_non_printable(char *str)
{
	unsigned int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] < ' ' || str[index] > '~')
			ft_print_hex(str[index]);
		else
			write(1, &str[index], 1);
		index++;
	}
}
