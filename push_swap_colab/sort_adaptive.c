/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:15:31 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/14 19:51:32 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adaptive_sort(t_stk *a, t_stk *b)
{
	while (a->len)
	{
		ft_printf("Pre-Push:\nA: ");
		for (int i = 0; i < a->len; i++)
			ft_printf("%d ", a->vals[i]);
		ft_printf("\nB: ");
		for (int i = 0; i < b->len; i++)
			ft_printf("%d ", b->vals[i]);
		ft_printf("\n");
		p(b, a);
		ft_printf("\n\n--------------------------------------------------\n\n");
		ft_printf("Post-Push:\nA: ");
		for (int i = 0; i < a->len; i++)
			ft_printf("%d ", a->vals[i]);
		ft_printf("\nB: ");
		for (int i = 0; i < b->len; i++)
			ft_printf("%d ", b->vals[i]);
		ft_printf("\n\n--------------------------------------------------\n\n");
	}
}
