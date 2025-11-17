/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_utils_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:23:06 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/17 01:05:27 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	slide_to_top_bottom_a(t_stk *a, t_stk *b, t_lists *lsts)
{
	while (lsts->l1l)
	{
		if (a->vals[0] > b->vals[0] && b->len > 0)
		{
			p(b, a);
			lsts->l1l -= 1;
			continue ;
		}
		if (a->vals[0] < b->vals[b->len - 1] && b->len > 0)
		{
			p(b, a);
			r(b);
			lsts->l1l -= 1;
			continue ;
		}
		break ;
	}
}

void	small_merger(t_stk *a, t_stk *b, t_lists *lsts)
{
	int	rotator;

	slide_to_top_bottom_a(a, b, lsts);
	while (lsts->l1l && lsts->l2l)
	{		
		if (a->vals[0] < b->vals[b->len - 1] && b->len > 0)
		{
			p(b, a);
			r(b);
			lsts->l1l -= 1;
		}
		if (a->vals[0] < a->vals[lsts->l1l])
		{
			p(b, a);
			lsts->l1l -= 1;
		}
		else
		{
			rotator = 0;
			while (rotator++ < lsts->l1l - 1)
				r(a);
			s(a);
			p(b, a);
			while (--rotator > 0)
				rr(a);
			lsts->l2l -= 1;
		}
	}
}
