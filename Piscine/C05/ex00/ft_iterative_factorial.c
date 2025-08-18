/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:46:34 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/11 14:43:34 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_iterative_factorial(int nb)
{
	int	result;
	int	index;

	index = 1;
	result = 1;
	if (nb == 0)
		return (1);
	if (nb < 0)
		return (0);
	while (index <= nb)
	{
		result *= index;
		index++;
	}
	return (result);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%d\n", ft_iterative_factorial(10));
// 	printf("%d\n", ft_iterative_factorial(0));
// }
