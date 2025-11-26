/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ops2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:00:19 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/24 23:38:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	s(t_stk *stk)
{
	char const	*lbl[] = {"sa\n", "sb\n"};

	if (stk->len > 1)
	{
		swap(stk->vals);
		write(STDOUT_FILENO, lbl[stk->name - 'a'], 3);
	}
}

void	ss(t_stk *stk_1, t_stk *stk_2)
{
	if (stk_1->len > 1 && stk_2->len > 1)
	{
		swap(stk_1->vals);
		swap(stk_2->vals);
		write(STDOUT_FILENO, "ss\n", 3);
	}
}

void	p(t_stk *to, t_stk *from)
{
	int			val;
	char const	*lbl[] = {"pa\n", "pb\n"};

	if (from->len && (to->len < to->cap))
	{
		val = pop(from->vals, &from->len);
		push(val, to->vals, &to->len);
		write(STDOUT_FILENO, lbl[to->name - 'a'], 3);
	}
}

void	r(t_stk *stk)
{
	char const	*lbl[] = {"ra\n", "rb\n"};

	if (stk->len > 1)
	{
		rotate(stk->vals, stk->len);
		write(STDOUT_FILENO, lbl[stk->name - 'a'], 3);
	}	
}

void	rr(t_stk *stk)
{
	char const	*lbl[] = {"rra\n", "rrb\n"};

	if (stk->len > 1)
	{
		rrotate(stk->vals, stk->len);
		write(STDOUT_FILENO, lbl[stk->name - 'a'], 4);
	}
}
