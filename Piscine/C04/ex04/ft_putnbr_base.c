/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:38:55 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/10 17:07:24 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	ft_is_valid_base(char *base)
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

void	ft_putnbr_base(int nbr, char *base)
{
	int			base_len;
	long long	l_nbr;

	l_nbr = nbr;
	base_len = ft_strlen(base);
	if (ft_is_valid_base(base))
	{
		if (nbr < 0)
		{
			write(1, "-", 1);
			if (nbr == -2147483648)
				l_nbr = ~(long long)nbr + 1;
			else
				l_nbr = -nbr;
		}
		if (l_nbr > base_len - 1)
			ft_putnbr_base(l_nbr / base_len, base);
		write(1, &base[l_nbr % base_len], 1);
	}
}

// #include <limits.h>

// int	main(void)
// {
// 	int	nbr;

// 	nbr = INT_MIN;
// 	// write(1, "175 to dec: ", 12);
// 	// ft_putnbr_base(nbr, "0123456789");
// 	// write(1, "\n", 1);
// 	// write(1, "175 to hex: ", 12);
// 	// ft_putnbr_base(nbr, "0123456789abcdef");
// 	// write(1, "\n", 1);
// 	// write(1, "175 to oct: ", 12);
// 	// ft_putnbr_base(nbr, "01234567");
// 	// write(1, "\n", 1);
// 	// write(1, "175 to bin: ", 12);
// 	ft_putnbr_base(nbr, "01");
// 	write(1, "\n", 1);
// }
