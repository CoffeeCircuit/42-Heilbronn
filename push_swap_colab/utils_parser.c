/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:39:52 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/12 09:37:07 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parse_bench(t_flag *flags, char const *arg)
{
	if (ft_memcmp(arg, "--bench", 8) == 0)
	{
		flags->bench_set++;
		return (1);
	}
	return (0);
}

int	parse_strat(t_flag *flags, char const *arg)
{
	if (ft_memcmp(arg, "--simple", 9) == 0)
		flags->strategy = SIMPLE;
	else if (ft_memcmp(arg, "--medium", 9) == 0)
		flags->strategy = MEDIUM;
	else if (ft_memcmp(arg, "--complex", 10) == 0)
		flags->strategy = COMPLEX;
	else if (ft_memcmp(arg, "--adaptive", 11) == 0)
		flags->strategy = ADAPTIVE;
	else
		return (0);
	flags->strat_set++;
	return (1);
}

int	parse_flag(t_flag *flags, int *pos, int argc, char const *argv[])
{
	while (*pos < argc && !is_num(argv[*pos]) && !ft_strchr(argv[*pos], ' '))
	{
		flags->valid_flag += parse_strat(flags, argv[*pos]);
		flags->valid_flag += parse_bench(flags, argv[*pos]);
		if (!flags->valid_flag)
			return (perror(), 0);
		if (flags->strat_set > 1 || flags->bench_set > 1)
			return (perror(), 0);
		(*pos)++;
	}
	return (1);
}

int	contains(int *arr, int nbr, size_t len)
{
	if (!len || !arr)
		return (0);
	while (len--)
	{
		if (*arr == nbr)
			return (1);
		arr++;
	}
	return (0);
}

int	parse_numargs(t_stk *stk, int *pos, int argc, char const *argv[])
{
	stk->sts->strategy = stk->flgs->strategy;
	while (*pos < argc)
	{
		if (!parse_args_str(stk, &stk->len, argv[*pos]))
			return (free(stk->vals), perror(), 0);
		(*pos)++;
	}
	if (!stk->len)
		return (free(stk->vals), perror(), 0);
	return (1);
}
