/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:45:35 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/11 12:50:07 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_power(int nb, int power)
{
	int	exp;
	int	result;

	exp = 0;
	result = 1;
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	while (exp < power)
	{
		result *= nb;
		exp++;
	}
	return (result);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d\n", ft_iterative_power(2, 5));
// 	printf("%d\n", ft_iterative_power(2, -2));
// 	printf("%d\n", ft_iterative_power(2, 0));
// }
