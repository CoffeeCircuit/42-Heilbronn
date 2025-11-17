/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_utils_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:36:24 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/17 03:21:47 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

void	slide_to_top_bottom_b(t_stk *a, t_stk *b, size_t *list)
{
	while (*list)
	{
		if (b->vals[0] < a->vals[0] && a->len > 0)
		{
			p(a, b);
			*list -= 1;
			continue ;
		}
		if (b->vals[0] > a->vals[a->len - 1] && a->len > 0)
		{
			p(a, b);
			r(a);
			*list -= 1;
			continue ;
		}
		break ;
	}
}

void	big_merger_list_1(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst)
{
	int	rotator;

	if (b->vals[0] > a->vals[a->len - 1] && a->len > 0)
	{
		p(a, b);
		r(a);
		lsts->l1l -= 1;
	}
	else if (b->vals[0] > b->vals[lsts->l1l])
	{
		p(a, b);
		lsts->l1l -= 1;
	}
	else
	{
		switch_sublist(lsts, b, active_lst);
	}
}

void	big_merger_list_2(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst)
{
	int	rotator;

	if (b->vals[0] > a->vals[a->len - 1] && a->len > 0)
	{
		p(a, b);
		r(a);
		lsts->l2l -= 1;
	}
	else if (b->vals[0] > b->vals[b->len - lsts->l1l])
	{
		p(a, b);
		lsts->l2l -= 1;
	}
	else
	{
		switch_sublist(lsts, b, active_lst);
	}
}
