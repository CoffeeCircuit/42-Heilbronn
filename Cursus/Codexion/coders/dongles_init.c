/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:48:14 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/13 08:01:43 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	dongle_mutex_cond_init(t_dongle *dongle)
{
	int	rc;

	dongle->is_init = false;
	rc = pthread_mutex_init(&dongle->lock_dongle, NULL);
	if (rc != 0)
		return (rc);
	rc = pthread_cond_init(&dongle->cond_free, NULL);
	if (rc != 0)
	{
		pthread_mutex_destroy(&dongle->lock_dongle);
		return (rc);
	}
	dongle->is_init = true;
	return (0);
}

static void	dongle_mutex_cond_destory(t_dongle *dongle)
{
	if (dongle->is_init)
	{
		pthread_cond_destroy(&dongle->cond_free);
		pthread_mutex_destroy(&dongle->lock_dongle);
		dongle->is_init = false;
	}
}

static int	queue_init(t_queue *queue, int size)
{
	queue->q_len = 0;
	queue->q_cap = size;
	queue->entries = (t_qentry *)malloc(sizeof(t_qentry) * size);
	if (!queue->entries)
	{
		queue->entries = NULL;
		return (0);
	}
	return (1);
}

void	dongles_destroy(t_dongle *dongles, int i)
{
	i--;
	while (i >= 0)
	{
		dongle_mutex_cond_destory(&dongles[i]);
		if (dongles[i].queue)
		{
			if (dongles[i].queue->entries)
				free(dongles[i].queue->entries);
			free(dongles[i].queue);
			dongles[i].queue = NULL;
		}
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
		if (dongle_mutex_cond_init(&sim->dongles[i]) != 0)
			return (dongles_destroy(sim->dongles, i), 0);
		sim->dongles[i].id = i;
		sim->dongles[i].is_free = true;
		sim->dongles[i].cooldown = sim->dongle_cooldown;
		sim->dongles[i].ts_last_release.tv_sec = sim->sim_start.tv_sec - 1;
		sim->dongles[i].ts_last_release.tv_usec = sim->sim_start.tv_usec;
		sim->dongles[i].queue = (t_queue *)malloc(sizeof(t_queue));
		if (!sim->dongles[i].queue)
			return (dongles_destroy(sim->dongles, i), 0);
		if (!queue_init(sim->dongles[i].queue, sim->number_of_coders))
			return (dongles_destroy(sim->dongles, i), 0);
		i++;
	}
	return (1);
}
