/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_utils_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:23:06 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/18 06:23:22 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

void	slide_to_top_bottom_a(t_stk *a, t_stk *b, size_t *list)
{
	while (*list)
	{
		if (a->vals[0] > b->vals[0] && b->len > 0)
		{
			p(b, a);
			*list -= 1;
			continue ;
		}
		if (a->vals[0] < b->vals[b->len - 1] && b->len > 0)
		{
			p(b, a);
			r(b);
			*list -= 1;
			continue ;
		}
		break ;
	}
}

void	small_merger_list_1(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst)
{
	if (a->vals[0] < a->vals[lsts->l1l])
	{
		p(b, a);
		lsts->l1l -= 1;
	}
	else
	{
		switch_sublist(lsts, a, active_lst);
	}
}

void	small_merger_list_2(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst)
{
	if (a->vals[0] < a->vals[a->len - lsts->l1l])
	{
		p(b, a);
		lsts->l2l -= 1;
	}
	else
	{
		switch_sublist(lsts, a, active_lst);
	}
}
