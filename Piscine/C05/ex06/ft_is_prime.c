/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 14:13:48 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/11 16:08:31 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	long long	test;

	test = 2;
	if (nb < 2)
		return (0);
	while (test * test <= nb)
	{
		if (nb % test == 0)
			return (0);
		test++;
	}
	return (1);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%d", ft_is_prime(2147483647));
// }
