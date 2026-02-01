/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 02:50:25 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 04:02:43 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <pthread.h>

static int	init_coder_attr(t_sim *sim)
{
	int		i;
	t_coder	*coders;

	i = 0;
	coders = sim->coders;
	while (i < sim->number_of_coders)
	{
		coders[i].id = i;
		coders[i].compilations = 0;
		coders[i].state = OK;
		coders[i].ldongle = &sim->dongles[(2 * i - 1 + sim->number_of_coders)
			% sim->number_of_coders];
		coders[i].rdongle = &sim->dongles[(2 * i + 1) % sim->number_of_coders];
		coders[i].ts_burnout = sim->sim_start;
		update_timeout(&coders[i].ts_burnout, sim->time_to_burnout);
		if (pthread_mutex_init(&coders[i].state_lock, NULL) != 0)
			return (0);
		if (pthread_cond_init(&coders[i].state_cond, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	init_dongle_attr(t_sim *sim)
{
	int			i;
	t_dongle	*dongles;

	i = 0;
	dongles = sim->dongles;
	while (i < sim->number_of_coders)
	{
		dongles[i].id = i;
		dongles[i].is_free = 1;
		dongles[i].cooldown_duration = sim->dongle_cooldown;
		dongles[i].strat = sim->scheduler;
		dongles[i].queue = (t_queue *)malloc(sizeof(t_queue));
		if (!dongles[i].queue)
			return (0);
		if (pthread_mutex_init(&dongles[i].dongle_lock, NULL) != 0)
			return (0);
		if (pthread_cond_init(&dongles[i].free_cond, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_sim(t_sim *sim)
{
	sim->sim_stop = 0;
	sim->coders = NULL;
	sim->dongles = NULL;
	gettimeofday(&sim->sim_start, NULL);
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&sim->sim_stop_lock, NULL) != 0)
		return (0);
	if (pthread_cond_init(&sim->sim_stop_cond, NULL) != 0)
		return (0);
	sim->coders = (t_coder *)malloc(sim->number_of_coders * sizeof(t_coder));
	if (!sim->coders)
		return (0);
	sim->dongles = (t_dongle *)malloc(sim->number_of_coders * sizeof(t_dongle));
	if (!sim->dongles)
		return (0);
	if (!init_coder_attr(sim) || !init_dongle_attr(sim))
		return (0);
	return (1);
}

void	join_threads(t_sim *sim)
{
	int	i;

	i = 0;
	/* TODO
		sim->monitor is only joined if it was actually created
		coder threads are only joined if creation succeeded for them all
		(or you track how many were created)
		*/
	while (i < sim->number_of_coders)
		pthread_join(sim->coders[i++].job, NULL);
	pthread_join(sim->monitor, NULL);
}

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
		i = 0;
	}
	if (sim->dongles)
	{
		while (i < sim->number_of_coders)
		{
			pthread_mutex_destroy(&sim->dongles[i].dongle_lock);
			pthread_cond_destroy(&sim->dongles[i].free_cond);
			free(sim->dongles[i].queue);
			i++;
		}
		free(sim->dongles);
	}
	pthread_mutex_destroy(&sim->print_lock);
	pthread_mutex_destroy(&sim->sim_stop_lock);
	pthread_cond_destroy(&sim->sim_stop_cond);
}
