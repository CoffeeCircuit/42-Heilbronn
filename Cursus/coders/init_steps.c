/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:30:18 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 22:41:58 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	unwind(void *ctx, int int_args[2], int count, t_step *steps)
{
	int	step_i;
	int	item_i;

	step_i = int_args[0];
	item_i = int_args[1];
	while (--item_i >= 0)
		steps[step_i].cleanup(ctx, item_i);
	while (--step_i >= 0)
	{
		item_i = count;
		while (--item_i >= 0)
			steps[step_i].cleanup(ctx, item_i);
	}
}

int	run_init_steps(void *ctx, int count, int num_steps, t_step *steps)
{
	int	int_args[2];

	int_args[0] = 0;
	while (int_args[0] < num_steps)
	{
		int_args[1] = 0;
		while (int_args[1] < count)
		{
			if (!steps[int_args[0]].init(ctx, int_args[1]))
			{
				unwind(ctx, int_args, count, steps);
				return (0);
			}
			int_args[1]++;
		}
		int_args[0]++;
	}
	return (1);
}
