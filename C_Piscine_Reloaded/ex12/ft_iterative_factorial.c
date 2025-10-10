/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:23:53 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/10 11:24:05 by abalcu           ###   ########.fr       */
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
