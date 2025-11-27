/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:15:44 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/26 23:37:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_a(t_stk *a)
{
	int	*tmp;

	tmp = val_to_idx(a->vals, a->len);
	free(a->vals);
	a->vals = tmp;
}

static void	chunk(t_mcounter *counter, t_limit *cnks, t_stk *a, t_stk *b)
{
	int	mid;

	if (counter->p < (int)a->len / 2)
		while ((counter->p)--)
			r(a);
	else
	{
		counter->p = a->len - counter->p;
		while ((counter->p)--)
			rr(a);
	}
	mid = (cnks[counter->i].min + cnks[counter->i].max) / 2;
	if (a->vals[0] < mid)
	{
		p(b, a);
		r(b);
	}
	else
		p(b, a);
}

static void	move_a(t_stk *a, t_stk *b)
{
	size_t	max_i;

	max_i = max_index(b->vals, b->len);
	if (max_i < b->len / 2)
		while (max_i--)
			r(b);
	else
	{
		max_i = b->len - max_i;
		while (max_i--)
			rr(b);
	}
	p(a, b);
}

static int	chunck_count(int len)
{
	if (len <= 10)
		return (1);
	else if (len <= 100)
		return (5);
	else if (len <= 500)
		return (10);
	else
		return (len / 25);
}

// Chunk sorting
void	ps_sort(t_stk *a, t_stk *b)
{
	int			cnk_c;
	t_limit		*cnks;
	t_mcounter	counter;

	cnk_c = chunck_count(a->len);
	counter = (t_mcounter){0};
	index_a(a);
	cnks = get_chunck_range(a->len, cnk_c);
	while (counter.i <= cnk_c)
	{
		while (1)
		{
			counter.p = find_next_in_chunk(a->vals, a->len, cnks[counter.i]);
			if (counter.p == -1)
				break ;
			chunk(&counter, cnks, a, b);
		}
		counter.i++;
	}
	while (b->len)
		move_a(a, b);
	free(cnks);
}
