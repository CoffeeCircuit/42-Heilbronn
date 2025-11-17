/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:55:24 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/13 00:57:01 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Max's bubble sort
void	simple_sort(t_stk *a, t_stk *b)
{
	size_t	index;

	while (a->len - 2 && get_disorder(a->vals, a->len))
	{
		index = 0;
		while (index < a->len - 1)
		{
			rr(a);
			if (a->vals[0] > a->vals[1])
				s(a);
			index++;
		}
		p(b, a);
	}
	if (a->vals[0] > a->vals[1])
		s(a);
	while (b->len)
	{
		p(a, b);
	}
}
