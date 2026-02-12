/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 02:49:37 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/12 09:33:07 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	sim_mutex_cond_init(t_sim *sim)
{
	int	rc;

	sim->is_init = false;
	rc = pthread_mutex_init(&sim->lock_sim, NULL);
	if (rc != 0)
		return (rc);
	rc = pthread_mutex_init(&sim->lock_print, NULL);
	if (rc != 0)
	{
		pthread_mutex_destroy(&sim->lock_sim);
		return (rc);
	}
	rc = pthread_cond_init(&sim->cond_sim, NULL);
	if (rc != 0)
	{
		pthread_mutex_destroy(&sim->lock_print);
		pthread_mutex_destroy(&sim->lock_sim);
		return (rc);
	}
	sim->is_init = true;
	return (0);
}

static void	sim_mutex_cond_destory(t_sim *sim)
{
	if (sim->is_init)
	{
		pthread_cond_destroy(&sim->cond_sim);
		pthread_mutex_destroy(&sim->lock_print);
		pthread_mutex_destroy(&sim->lock_sim);
		sim->is_init = false;
	}
}

void	sim_destroy(t_sim *sim)
{
	dongles_destroy(sim->dongles, sim->number_of_coders);
	coders_destroy(sim->coders, sim->number_of_coders);
	if (sim->finished_coders)
		free(sim->finished_coders);
	sim_mutex_cond_destory(sim);
}

int	sim_init(t_sim *sim)
{
	if (sim_mutex_cond_init(sim) != 0)
		return (sim_destroy(sim), 0);
	sim->finished_coders = (char *)malloc(sim->number_of_coders + 1);
	if (!sim->finished_coders)
		return (sim_destroy(sim), 0);
	memset(sim->finished_coders, 0, sim->number_of_coders + 1);
	sim->sim_stop = false;
	gettimeofday(&sim->sim_start, NULL);
	if (!dongles_init(sim))
		return (sim_destroy(sim), 0);
	if (!coders_init(sim))
		return (sim_destroy(sim), 0);
	return (1);
}
