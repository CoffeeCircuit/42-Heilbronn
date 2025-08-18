/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:23:45 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/04 11:21:23 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define MAX_ARRAY_LEN 12

// max unsigned int is -2147483648 to 2147483647
// this means max 12 chars (10 digits + sign char + null byte at the end)
// using a variation on Euclids method
void	ft_putnbr(int nb)
{
	int		index;
	char	temp_char;
	char	buf[MAX_ARRAY_LEN];

	index = 0;
	if (nb < 0)
		write(1, "-", 1);
	while (index < MAX_ARRAY_LEN)
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
