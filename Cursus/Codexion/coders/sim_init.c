/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 02:49:37 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 10:55:51 by abalcu           ###   ########.fr       */
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
		return (pthread_mutex_destroy(&sim->lock_sim), rc);
	rc = pthread_mutex_init(&sim->lock_sched, NULL);
	if (rc != 0)
		return (pthread_mutex_destroy(&sim->lock_print),
			pthread_mutex_destroy(&sim->lock_sim), rc);
	rc = pthread_cond_init(&sim->cond_sim, NULL);
	if (rc != 0)
		return (pthread_mutex_destroy(&sim->lock_sched),
			pthread_mutex_destroy(&sim->lock_print),
			pthread_mutex_destroy(&sim->lock_sim), rc);
	rc = pthread_cond_init(&sim->cond_sched, NULL);
	if (rc != 0)
		return (pthread_cond_destroy(&sim->cond_sim),
			pthread_mutex_destroy(&sim->lock_sched),
			pthread_mutex_destroy(&sim->lock_print),
			pthread_mutex_destroy(&sim->lock_sim), rc);
	return (sim->is_init = true, 0);
}

static void	sim_mutex_cond_destory(t_sim *sim)
{
	if (sim->is_init)
	{
		pthread_cond_destroy(&sim->cond_sched);
		pthread_cond_destroy(&sim->cond_sim);
		pthread_mutex_destroy(&sim->lock_sched);
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
	if (sim->global_queue)
	{
		if (sim->global_queue->entries)
			free(sim->global_queue->entries);
		free(sim->global_queue);
	}
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
	sim->global_queue = (t_queue *)malloc(sizeof(t_queue));
	if (!sim->global_queue)
		return (sim_destroy(sim), 0);
	sim->global_queue->q_len = 0;
	sim->global_queue->q_cap = sim->number_of_coders;
	sim->global_queue->entries = (t_qentry *)malloc(sizeof(t_qentry)
			* sim->number_of_coders);
	if (!sim->global_queue->entries)
		return (sim_destroy(sim), 0);
	sim->sim_stop = false;
	gettimeofday(&sim->sim_start, NULL);
	if (!dongles_init(sim))
		return (sim_destroy(sim), 0);
	if (!coders_init(sim))
		return (sim_destroy(sim), 0);
	return (1);
}
