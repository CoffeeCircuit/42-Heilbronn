/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 04:43:20 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

static int	dongle_mutex_init(void *ctx, int i)
{
	return (pthread_mutex_init(&((t_sim *)ctx)->dongles[i].dongle_lock,
			NULL) == 0);
}

static int	dongle_cond_init(void *ctx, int i)
{
	return (pthread_cond_init(&((t_sim *)ctx)->dongles[i].free_cond,
			NULL) == 0);
}

static void	dongle_mutex_cleanup(void *ctx, int i)
{
	pthread_mutex_destroy(&((t_sim *)ctx)->dongles[i].dongle_lock);
}

static void	dongle_cond_cleanup(void *ctx, int i)
{
	pthread_cond_destroy(&((t_sim *)ctx)->dongles[i].free_cond);
}

int	init_dongles(t_sim *sim)
{
	int				i;
	t_dongle		*dongles;
	static t_step	steps[] = {{dongle_mutex_init, dongle_mutex_cleanup},
			{dongle_cond_init, dongle_cond_cleanup}};

	i = 0;
	dongles = sim->dongles;
	if (!run_init_steps(sim, sim->number_of_coders, sizeof(steps)
			/ sizeof(steps[0]), steps))
		return (0);
	while (i < sim->number_of_coders)
	{
		dongles[i].id = i;
		dongles[i].is_free = 1;
		dongles[i].cooldown_duration = sim->dongle_cooldown;
		dongles[i].strat = sim->scheduler;
		if (!init_queue(&dongles[i].queue, 2 * sim->number_of_coders))
		{
			while (--i >= 0)
			{
				free(dongles[i].queue->entries);
				free(dongles[i].queue);
			}
			return (0);
		}
		i++;
	}
	return (1);
}
