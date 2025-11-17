/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:27:26 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 18:32:24 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	int	position;
	int	digit;

	position = 1000000000;
	if (n < 0)
		write(fd, "-", 1);
	while (n / (position) == 0 && position > 1)
		position /= 10;
	while (position >= 1)
	{
		digit = n / position;
		if (digit < 0)
			digit *= -1;
		if (n < 0)
			n = n + (digit * position);
		else
			n = n - (digit * position);
		digit += 48;
		write(fd, &digit, 1);
		position /= 10;
	}
}
