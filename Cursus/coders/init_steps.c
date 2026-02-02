/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 02:30:18 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/02 02:30:21 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	run_init_steps(void *ctx, int count, t_step *steps)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!steps[i].init(ctx, i))
		{
			while (--i >= 0)
				steps[i].cleanup(ctx, i);
			return (0);
		}
	}
	return (1);
}
