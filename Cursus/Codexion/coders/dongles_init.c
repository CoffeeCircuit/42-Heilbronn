/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:48:14 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 11:42:38 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	dongle_mutex_init(t_dongle *dongle)
{
	int	rc;

	dongle->is_init = false;
	rc = pthread_mutex_init(&dongle->lock_dongle, NULL);
	if (rc != 0)
		return (rc);
	dongle->is_init = true;
	return (0);
}

static void	dongle_mutex_destroy(t_dongle *dongle)
{
	if (dongle->is_init)
	{
		pthread_mutex_destroy(&dongle->lock_dongle);
		dongle->is_init = false;
	}
}

void	dongles_destroy(t_dongle *dongles, int i)
{
	i--;
	while (i >= 0)
	{
		dongle_mutex_destroy(&dongles[i]);
		i--;
	}
	free(dongles);
}

int	dongles_init(t_sim *sim)
{
	int	i;

	i = 0;
	sim->dongles = (t_dongle *)malloc(sizeof(t_dongle) * sim->number_of_coders);
	if (!sim->dongles)
		return (0);
	while (i < sim->number_of_coders)
	{
		if (dongle_mutex_init(&sim->dongles[i]) != 0)
			return (dongles_destroy(sim->dongles, i), 0);
		sim->dongles[i].id = i;
		sim->dongles[i].is_free = true;
		sim->dongles[i].cooldown = sim->dongle_cooldown;
		sim->dongles[i].ts_last_release.tv_sec = sim->sim_start.tv_sec - 1;
		sim->dongles[i].ts_last_release.tv_usec = sim->sim_start.tv_usec;
		i++;
	}
	return (1);
}

void	dongles_init_lock(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&coder->ldongle->lock_dongle);
	pthread_mutex_lock(&coder->rdongle->lock_dongle);
	coder->ldongle->is_free = false;
	coder->rdongle->is_free = false;
	pthread_mutex_unlock(&coder->rdongle->lock_dongle);
	pthread_mutex_unlock(&coder->ldongle->lock_dongle);
	queue_pop(sim->global_queue, coder);
	pthread_mutex_unlock(&sim->lock_sched);
	log_action(coder, ACT_DONGLE_PICK);
	log_action(coder, ACT_DONGLE_PICK);
}
