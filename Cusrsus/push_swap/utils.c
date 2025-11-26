/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 07:30:34 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/26 01:36:33 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	ft_strtol(char const *nptr)
{
	long	result;
	int		negate;
	int		i;

	i = 0;
	negate = 1;
	result = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negate = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * negate);
}

static int	is_int(char const *arg)
{
	long	num;
	int		dcount;

	num = ft_strtol(arg);
	dcount = ft_strlen(arg);
	if ((num < 0 && num < INT_MIN) || dcount > 11)
		return (0);
	if ((num > 0 && num > INT_MAX) || dcount > 11)
		return (0);
	return (1);
}

int	is_num(char const *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	if (!arg[i] || !is_int(arg))
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_perror(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
}
