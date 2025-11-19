/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:15:33 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/18 21:55:25 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

void	switch_sublist(t_lists *lsts, t_stk *stk, int *active_list)
{
	int	rotator;

	rotator = 0;
	if (lsts->l1l == 1 && lsts->l2l == 1 && *active_list == 1)
		s(stk);
	else
	{
		while (rotator++ < lsts->l1l)
		{
			if (*active_list == 1)
				r(stk);
			else
				rr(stk);
		}
		if (*active_list == 1)
			*active_list = 2;
		else
			*active_list = 1;
	}
}

void	empty_b(t_stk *stk_1, t_stk *stk_2)
{
	while (stk_2->len)
		p(stk_1, stk_2);
}

void	merge_from_a(t_stk *stk_1, t_stk *stk_2, t_mrg *mrg)
{
	t_lists	lsts;
	int		active_list;

	active_list = 2;
	lsts.l2l = get_first_list_size_a(stk_1);
	lsts.l1l = get_last_list_size_a(stk_1, lsts.l2l);
	lsts.l3l = stk_2->len;
	while (lsts.l1l || lsts.l2l || lsts.l3l)
	{
		if (active_list == 1)
			small_merger_list_1(stk_1, stk_2, &lsts, &active_list);
		else
			small_merger_list_2(stk_1, stk_2, &lsts, &active_list);
	}
	if (active_list == 2)
		switch_sublist(&lsts, stk_1, &active_list);
	while (lsts.l1l--)
		p(stk_2, stk_1);
	while (lsts.l2l--)
		p(stk_2, stk_1);
}

void	merge_from_b(t_stk *stk_1, t_stk *stk_2, t_mrg *mrg)
{
	t_lists	lsts;
	int		active_list;

	active_list = 1;
	lsts.l1l = get_first_list_size_b(stk_2);
	lsts.l2l = get_last_list_size_b(stk_2, lsts.l2l);
	while (lsts.l1l && lsts.l2l)
	{
		if (active_list == 1)
			big_merger_list_1(stk_1, stk_2, &lsts, &active_list);
		else
			big_merger_list_2(stk_1, stk_2, &lsts, &active_list);
	}
	if (active_list == 2)
		switch_sublist(&lsts, stk_2, &active_list);
	while (lsts.l1l--)
		p(stk_1, stk_2);
	while (lsts.l2l--)
		p(stk_1, stk_2);
}

void	complex_sort(t_stk *a, t_stk *b)
{
	t_mrg	mrg;

	mrg.sublist_size = 1;
	mrg.sublist_count = a->len;
	mrg.full_size = mrg.sublist_count;
	while (1)
	{
		if (get_disorder(a->vals, a->len) == 0 && b->len == 0)
			break ;
		if (get_disorder(b->vals, b->len) == 1 && a->len == 0)
			break ;
		merge_from_a(a, b, &mrg);
	}
	while (b->len)
		p(a, b);
}
