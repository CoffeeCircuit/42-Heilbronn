/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:33:23 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/09 15:13:00 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
