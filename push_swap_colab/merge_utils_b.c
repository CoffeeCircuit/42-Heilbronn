/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_utils_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 03:36:24 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/17 01:06:27 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	slide_to_top_bottom_b(t_stk *a, t_stk *b, t_lists *lsts)
{
	while (lsts->l1l)
	{
		if (b->vals[0] < a->vals[0] && a->len > 0)
		{
			p(a, b);
			lsts->l1l -= 1;
			continue ;
		}
		if (b->vals[0] > a->vals[a->len - 1] && a->len > 0)
		{
			p(a, b);
			r(a);
			lsts->l1l -= 1;
			continue ;
		}
		break ;
	}
}

void	big_merger(t_stk *a, t_stk *b, t_lists *lsts)
{
	int	rotator;

	slide_to_top_bottom_b(a, b, lsts);
	while (lsts->l1l && lsts->l2l)
	{
		if (b->vals[0] > a->vals[a->len - 1] && a->len > 0)
		{
			p(a, b);
			r(a);
			lsts->l1l -= 1;
		}
		if (b->vals[0] > b->vals[lsts->l1l])
		{
			p(a, b);
			lsts->l1l -= 1;
		}
		else
		{
			rotator = 0;
			while (rotator++ < lsts->l1l - 1)
				r(b);
			s(b);
			p(a, b);
			while (--rotator > 0)
				rr(b);
			lsts->l2l -= 1;
		}
	}
}
