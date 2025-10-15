/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 08:49:28 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/15 03:47:06 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rec_putnbr(int n, int fd)
{
	long long		nbr;
	unsigned char	chr;

	if (n == 0)
		return ;
	nbr = (long long)n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = -nbr;
	}
	ft_rec_putnbr(nbr / 10, fd);
	chr = '0' + (nbr % 10);
	write(fd, &chr, 1);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	ft_rec_putnbr(n, fd);
	return ;
}
