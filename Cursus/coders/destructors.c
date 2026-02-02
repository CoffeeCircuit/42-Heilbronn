/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 00:23:57 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/02 03:30:50 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_sim(t_sim *sim)
{
	int	i;

	i = 0;
	if (sim->coders)
	{
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->coders[i].state_lock);
			pthread_cond_destroy(&sim->coders[i].state_cond);
			i++;
		}
		free(sim->coders);
	}
	i = 0;
	if (sim->dongles)
	{
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->dongles[i].dongle_lock);
			pthread_cond_destroy(&sim->dongles[i].free_cond);
			if (sim->dongles[i].queue)
			{
				free(sim->dongles[i].queue->entries);
				free(sim->dongles[i].queue);
			}
			i++;
		}
		free(sim->dongles);
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->sim_stop_lock);
	pthread_cond_destroy(&sim->sim_stop_cond);
}
