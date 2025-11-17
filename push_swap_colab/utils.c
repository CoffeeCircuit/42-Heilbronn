/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 07:30:34 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/12 05:11:46 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	get_disorder(int *stack, int size)
{
	unsigned int	mistakes;
	unsigned int	pairs;
	int				i;
	int				j;

	i = 0;
	pairs = 0;
	mistakes = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			pairs++;
			if (stack[i] > stack[j])
				mistakes++;
			j++;
		}
		i++;
	}
	return ((float)mistakes / pairs);
}

int	is_num(char const *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	perror(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
}
