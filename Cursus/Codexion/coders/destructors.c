/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:23:57 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 22:18:17 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

static int	pth_dest(pthread_mutex_t *mutex, pthread_cond_t *cond)
{
	return (pthread_mutex_destroy(mutex) == 0
		&& pthread_cond_destroy(cond) == 0);
}

void	destroy_sim(t_sim *sim)
{
	int	i;

	i = -1;
	if (sim->coders)
	{
		while (++i < sim->number_of_coders)
			pth_dest(&sim->coders[i].state_lock, &sim->coders[i].state_cond);
		free(sim->coders);
	}
	i = -1;
	if (sim->dongles)
	{
		while (++i < sim->number_of_coders)
		{
			pth_dest(&sim->dongles[i].dongle_lock, &sim->dongles[i].free_cond);
			if (sim->dongles[i].queue)
			{
				free(sim->dongles[i].queue->entries);
				free(sim->dongles[i].queue);
			}
		}
		free(sim->dongles);
	}
	pthread_mutex_destroy(&sim->print_lock);
	pth_dest(&sim->sim_stop_lock, &sim->sim_stop_cond);
}
