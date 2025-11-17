/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 00:50:38 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/12 05:11:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ptos(double nbr)
{
	char	*out;
	int		n;

	out = (char *)ft_calloc(7, sizeof(char));
	n = (int)(nbr * 100);
	ft_memcpy(out, ft_itoa(n), ft_strlen(ft_itoa(n)));
	ft_memcpy(&out[ft_strlen(out)], ".", 1);
	n = (int)(nbr * 10000) % 100;
	ft_memcpy(&out[ft_strlen(out)], ft_itoa(n), ft_strlen(ft_itoa(n)));
	ft_memcpy(&out[ft_strlen(out)], "%", 1);
	return (out);
}

void	pstat_f(char *desc, double val, int has_nl, int has_bench)
{
	char	*out;

	out = ptos(val);
	if (has_bench)
		write(STDERR_FILENO, "[bench] ", 8);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, out, ft_strlen(out));
	if (has_nl)
		write(STDERR_FILENO, "\n", 1);
	free(out);
}

void	pstat_i(char *desc, int val, int has_nl, int has_bench)
{
	char	*out;

	out = ft_itoa(val);
	if (has_bench)
		write(STDERR_FILENO, "[bench] ", 8);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, out, ft_strlen(out));
	if (has_nl)
		write(STDERR_FILENO, "\n", 1);
	free(out);
}

void	pstat_s(char *desc, char *val, int has_nl, int has_bench)
{
	if (has_bench)
		write(STDERR_FILENO, "[bench] ", 8);
	write(STDERR_FILENO, desc, ft_strlen(desc));
	write(STDERR_FILENO, val, ft_strlen(val));
	if (has_nl)
		write(STDERR_FILENO, "\n", 1);
}

void	pbench(t_stat *sts)
{
	char		*val;
	char const	*strat[] = {"Adaptive", "Simple", "Medium", "Complex"};

	pstat_f("disorder: ", sts->disorder, 1, 1);
	pstat_s("strategy: ", (char *)strat[sts->strategy], 1, 1);
	pstat_i("total_ops: ", sts->ops, 1, 1);
	pstat_i("sa: ", sts->s[0], 0, 1);
	pstat_i("  sb: ", sts->s[1], 0, 0);
	pstat_i("  ss: ", sts->ss, 0, 0);
	pstat_i("  pa: ", sts->p[0], 0, 0);
	pstat_i("  pb: ", sts->p[1], 1, 0);
	pstat_i("ra: ", sts->r[0], 0, 1);
	pstat_i("  rb: ", sts->r[1], 0, 0);
	pstat_i("  rr: ", sts->rr_, 0, 0);
	pstat_i("  rra: ", sts->rr[0], 0, 0);
	pstat_i("  rrb: ", sts->rr[1], 0, 0);
	pstat_i("  rrr: ", sts->rrr, 1, 0);
}
