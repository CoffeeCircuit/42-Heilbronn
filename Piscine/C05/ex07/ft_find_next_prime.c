/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:11:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/11 16:14:57 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INT_MAX 2147483647

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

int	ft_find_next_prime(int nb)
{
	int	temp;

	temp = nb;
	while (temp <= INT_MAX)
	{
		if (ft_is_prime(temp))
			return (temp);
		temp++;
	}
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	next;

// 	next = ft_find_next_prime(2147483647);
// 	printf("%d", next);
// }
