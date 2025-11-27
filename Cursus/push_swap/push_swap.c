/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:01:08 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/27 00:12:18 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_sorted(t_stk *stk)
{
	size_t	i;

	i = 1;
	while (i < stk->len)
	{
		if (stk->vals[i - 1] > stk->vals[i])
			return (0);
		i++;
	}
	return (1);
}

static void	sort_3(t_stk *a)
{
	int const	i_0 = a->vals[0];
	int const	i_1 = a->vals[1];
	int const	i_2 = a->vals[2];

	if (i_0 < i_1 && i_1 > i_2 && i_2 > i_0)
	{
		rr(a);
		s(a);
	}
	if (i_0 > i_1 && i_1 < i_2 && i_2 > i_0)
		s(a);
	if (i_0 < i_1 && i_1 > i_2 && i_2 < i_0)
		rr(a);
	if (i_0 > i_1 && i_1 < i_2 && i_2 < i_0)
		r(a);
	if (i_0 > i_1 && i_1 > i_2 && i_2 < i_0)
	{
		r(a);
		s(a);
	}
}

static void	sort_5(t_stk *a, t_stk *b)
{
	size_t	two;
	size_t	max_i;

	two = a->len - 3;
	index_a(a);
	while (two--)
	{
		max_i = max_index(a->vals, a->len);
		if (max_i < (a->len / 2) + 1)
			while (max_i--)
				r(a);
		else
		{
			max_i = a->len - max_i;
			while (max_i--)
				rr(a);
		}
		p(b, a);
	}
	sort_3(a);
	while (b->len)
	{
		p(a, b);
		r(a);
	}
}

static void	ps_simple_sort(t_stk *a, t_stk *b)
{
	if (a->len == 2 && a->vals[0] > a->vals[1])
		s(a);
	if (a->len == 3)
		sort_3(a);
	if (a->len > 3 && a->len <= 5)
		sort_5(a, b);
}

int	main(int argc, char const *argv[])
{
	int		pos;
	t_stk	a;
	t_stk	b;

	if (argc < 2)
		return (1);
	pos = 1;
	a = (t_stk){.name = 'a', .len = 0, .vals = 0};
	b = (t_stk){.name = 'b', .len = 0, .vals = 0};
	if (!parse_numargs(&a, &pos, argc, argv))
		return (1);
	if (is_sorted(&a) || a.len == 1)
		return (0);
	b.vals = (int *)ft_calloc(a.cap, sizeof(int));
	if (!b.vals)
		return (free(a.vals), ft_perror(), 1);
	b.cap = a.cap;
	if (a.len <= 5)
		ps_simple_sort(&a, &b);
	else
		ps_sort(&a, &b);
	return (free(a.vals), free(b.vals), 0);
}
