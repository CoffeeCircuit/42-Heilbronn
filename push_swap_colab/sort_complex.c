/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:15:33 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/17 00:51:03 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	append_leftover_chunk(t_stk *to, t_stk *from, t_mrg *mrg)
{
	int	size;

	size = from->len;
	while (from->len)
		p(to, from);
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

	active_list = 1;
	while (stk_1->len)
	{
		lsts.l1l = get_first_list_size_a(stk_1);
		lsts.l2l = get_last_list_size_a(stk_1, lsts.l1l);
		small_merger(stk_1, stk_2, &lsts);
		while (lsts.l1l--)
			p(stk_2, stk_1);
		while (lsts.l2l--)
			p(stk_2, stk_1);
	}
}

void	merge_from_b(t_stk *stk_1, t_stk *stk_2, t_mrg *mrg)
{
	t_lists	lsts;
	int		active_list;

	active_list = 1;
	while (stk_2->len)
	{
		lsts.l1l = get_first_list_size_b(stk_2);
		lsts.l2l = get_last_list_size_b(stk_2, lsts.l1l);
		big_merger(stk_1, stk_2, &lsts);
		while (lsts.l1l--)
			p(stk_1, stk_2);
		while (lsts.l2l--)
			p(stk_1, stk_2);
	}
}

void	complex_sort(t_stk *a, t_stk *b)
{
	t_mrg	mrg;

	mrg.sublist_size = 1;
	mrg.sublist_count = a->len;
	mrg.full_size = mrg.sublist_count;
	while (1)
	{
		if (get_disorder(a->vals, a->len) == 0 && a->len != 0)
			break ;
		if (get_disorder(b->vals, b->len) == 1 && b->len != 0)
			break ;
		if (a->len)
			merge_from_a(a, b, &mrg);
		else
			merge_from_b(a, b, &mrg);
	}
	if (b->len)
		empty_b(a, b);
}
