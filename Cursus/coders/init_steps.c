/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:30:18 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 04:43:30 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	run_init_steps(void *ctx, int count, int num_steps, t_step *steps)
{
	int	step_i;
	int	item_i;

	step_i = 0;
	while (step_i < num_steps)
	{
		item_i = 0;
		while (item_i < count)
		{
			if (!steps[step_i].init(ctx, item_i))
			{
				while (--item_i >= 0)
					steps[step_i].cleanup(ctx, item_i);
				while (--step_i >= 0)
				{
					item_i = count;
					while (--item_i >= 0)
						steps[step_i].cleanup(ctx, item_i);
				}
				return (0);
			}
			item_i++;
		}
		step_i++;
	}
	return (1);
}
