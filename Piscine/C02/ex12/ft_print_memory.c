/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:50:35 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 14:25:30 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_addr(void *ptr, unsigned int *pos)
{
	int					index;
	unsigned long long	addr;
	char				result[17];

	result[16] = '\0';
	index = 15;
	addr = (unsigned long long)((char *)ptr + *pos);
	while (addr)
	{
		result[index] = "0123456789abcdef"[addr % 16];
		addr /= 16;
		index--;
	}
	while (index >= 0)
	{
		result[index] = '0';
		index--;
	}
	write(1, result, 16);
}

void	ft_print_hex(void *ptr, unsigned int *pos, unsigned int size)
{
	unsigned int	index;
	char			byte;

	index = 0;
	while (index < 16 && ((char *)ptr)[*pos] != '\0' && *pos < size)
	{
		byte = ((char *)ptr)[*pos];
		if (index > 0 && index % 2 == 0)
			write(1, " ", 1);
		write(1, &"0123456789abcdef"[byte / 16], 1);
		write(1, &"0123456789abcdef"[byte % 16], 1);
		index++;
		*pos += 1;
	}
	while (index < 16)
	{
		if (index > 0 && index % 2 == 0)
			write(1, " ", 1);
		if (((char *)ptr)[*pos] == '\0' && *pos < size)
			write(1, "00", 2);
		if (*pos >= size)
			write(1, "  ", 2);
		index++;
		*pos += 1;
	}
}

void	ft_print_char(void *ptr, unsigned int *pos, unsigned int size)
{
	unsigned int	index;
	char			byte;

	index = 0;
	*pos -= 16;
	while (index < 16 && ((char *)ptr)[*pos] != '\0' && *pos < size)
	{
		byte = ((char *)ptr)[*pos];
		if (byte < 32 || byte > 126)
			write(1, ".", 1);
		else
			write(1, &byte, 1);
		index++;
		*pos += 1;
	}
	while (index < 16)
	{
		if (((char *)ptr)[*pos] == '\0' && *pos < size)
			write(1, ".", 1);
		index++;
		*pos += 1;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	index;

	index = 0;
	if (size)
	{
		while (index < size)
		{
			ft_print_addr(addr, &index);
			write(1, ": ", 2);
			ft_print_hex(addr, &index, size);
			write(1, " ", 1);
			ft_print_char(addr, &index, size);
			if ((int)(size - index) >= 0)
				write(1, "\n", 1);
		}
	}
	return (addr);
}
