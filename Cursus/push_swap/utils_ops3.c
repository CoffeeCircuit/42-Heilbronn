/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ops3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 03:46:40 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/24 23:27:24 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rr_(t_stk *stk_1, t_stk *stk_2)
{
	if (stk_1->len > 1 && stk_2->len > 1)
	{
		rotate(stk_1->vals, stk_1->len);
		rotate(stk_2->vals, stk_2->len);
		write(STDOUT_FILENO, "rr\n", 3);
	}
}

void	rrr(t_stk *stk_1, t_stk *stk_2)
{
	if (stk_1->len > 1 && stk_2->len > 1)
	{
		rrotate(stk_1->vals, stk_1->len);
		rrotate(stk_2->vals, stk_2->len);
		write(STDOUT_FILENO, "rrr\n", 4);
	}
}
