/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:30:22 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/14 13:29:49 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(char *str);
int		ft_atoi_base(char *str, char *base);

int	ft_is_valid(char *base)
{
	char	lookup[256];
	int		index;

	index = 0;
	while (index < 256)
	{
		lookup[index] = 0;
		index++;
	}
	if (ft_strlen(base) <= 1)
		return (0);
	index = 0;
	while (base[index])
	{
		if (lookup[(int)base[index]] == 1)
			return (0);
		else if (base[index] == '+' || base[index] == '-')
			return (0);
		else if (lookup[(int)base[index]] == 0)
			lookup[(int)base[index]] = 1;
		index++;
	}
	return (1);
}

void	ft_putnbr_base(int nbr, char *base, char *buf, int index)
{
	int			base_len;
	long long	l_nbr;

	l_nbr = nbr;
	base_len = ft_strlen(base);
	if (ft_is_valid(base))
	{
		if (nbr < 0)
		{
			if (nbr == -2147483648)
				l_nbr = ~(long long)nbr + 1;
			else
				l_nbr = -nbr;
		}
		while (l_nbr)
		{
			buf[index] = base[l_nbr % base_len];
			l_nbr /= base_len;
			index++;
		}
		if (nbr < 0)
			buf[index] = '-';
	}
	else
		return ;
}

void	ft_zero(char buf[1024])
{
	int	index;

	index = 0;
	while (index <= 1024)
	{
		buf[index] = '\0';
		index++;
	}
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		decimal;
	int		index;
	char	*result;
	char	buf[1024];
	int		size;

	index = 0;
	ft_zero(buf);
	if (!(ft_is_valid(base_from)))
		return (NULL);
	if (!(ft_is_valid(base_to)))
		return (NULL);
	decimal = ft_atoi_base(nbr, base_from);
	ft_putnbr_base(decimal, base_to, buf, 0);
	size = ft_strlen(buf) + 1;
	result = (char *)malloc(size * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	index = -1;
	while (++index < size)
		result[index] = buf[size - index - 2];
	if (decimal == 0)
		*result = *base_to;
	return (result);
}
