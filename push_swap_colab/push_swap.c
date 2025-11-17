/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:43:22 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/16 19:25:40 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char const *argv[])
{
	int		pos;
	t_flag	flgs;
	t_stat	sts;
	t_stk	a;
	t_stk	b;

	if (argc < 2)
		return (perror(), 1);
	pos = 1;
	flgs = (t_flag){0};
	sts = (t_stat){0};
	a = (t_stk){.name = 'a', .flgs = &flgs, .sts = &sts, .len = 0, .vals = 0};
	b = (t_stk){.name = 'b', .flgs = &flgs, .sts = &sts, .len = 0, .vals = 0};
	if (!parse_flag(&flgs, &pos, argc, argv))
		return (1);
	if (!parse_numargs(&a, &pos, argc, argv))
		return (1);
	a.sts->disorder = get_disorder(a.vals, a.len);
	b.vals = (int *)ft_calloc(a.cap, sizeof(int));
	if (!b.vals)
		return (perror(), 1);
	b.cap = a.cap;
	ps_sort(&a, &b);
	return (free(a.vals), free(b.vals), 0);
}
