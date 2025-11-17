/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 03:46:40 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/12 05:11:39 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr_(t_stk *stk_1, t_stk *stk_2)
{
	if (stk_1->len > 1 && stk_2->len > 1)
	{
		rotate(stk_1->vals, stk_1->len);
		rotate(stk_2->vals, stk_2->len);
		stk_1->sts->ops++;
		stk_1->sts->rr_++;
		if (!stk_1->flgs->bench_set)
			write(STDOUT_FILENO, "rr\n", 3);
	}
}

void	rrr(t_stk *stk_1, t_stk *stk_2)
{
	if (stk_1->len > 1 && stk_2->len > 1)
	{
		rrotate(stk_1->vals, stk_1->len);
		rrotate(stk_2->vals, stk_2->len);
		stk_1->sts->ops++;
		stk_1->sts->rrr++;
		if (!stk_1->flgs->bench_set)
			write(STDOUT_FILENO, "rrr\n", 4);
	}
}
