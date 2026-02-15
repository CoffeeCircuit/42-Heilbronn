/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 05:31:31 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 11:47:55 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	dongles_available(t_coder *coder)
{
	t_dongle	*ldongle;
	t_dongle	*rdongle;
	bool		avail;
	long		time_since_release;

	ldongle = coder->ldongle;
	rdongle = coder->rdongle;
	pthread_mutex_lock(&ldongle->lock_dongle);
	pthread_mutex_lock(&rdongle->lock_dongle);
	avail = (ldongle->is_free && rdongle->is_free);
	if (avail)
	{
		time_since_release = get_timestamp(&ldongle->ts_last_release);
		if (time_since_release < ldongle->cooldown)
			avail = false;
		time_since_release = get_timestamp(&rdongle->ts_last_release);
		if (time_since_release < rdongle->cooldown)
			avail = false;
	}
	pthread_mutex_unlock(&rdongle->lock_dongle);
	pthread_mutex_unlock(&ldongle->lock_dongle);
	return (avail);
}

int	pick_dongles(t_coder *coder)
{
	t_sim			*sim;
	struct timespec	timeout;
	long			tdelta;

	sim = coder->sim;
	pthread_mutex_lock(&sim->lock_sched);
	queue_push(sim->global_queue, coder);
	while (true)
	{
		if (sim->sim_stop)
			return (queue_pop(sim->global_queue, coder),
				pthread_mutex_unlock(&sim->lock_sched), 0);
		tdelta = get_timestamp(&coder->ts_comp_start);
		if (tdelta >= sim->time_to_burnout)
			return (queue_pop(sim->global_queue, coder),
				pthread_mutex_unlock(&sim->lock_sched), 0);
		if (dongles_available(coder))
			if (coder == scheduler_select(sim->global_queue, sim->scheduler))
				return (dongles_init_lock(coder), 1);
		set_delay_ts(&timeout, 1);
		pthread_cond_timedwait(&sim->cond_sched, &sim->lock_sched, &timeout);
	}
	return (0);
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->ldongle->lock_dongle);
	coder->ldongle->is_free = true;
	gettimeofday(&coder->ldongle->ts_last_release, NULL);
	pthread_mutex_unlock(&coder->ldongle->lock_dongle);
	pthread_mutex_lock(&coder->rdongle->lock_dongle);
	coder->rdongle->is_free = true;
	gettimeofday(&coder->rdongle->ts_last_release, NULL);
	pthread_mutex_unlock(&coder->rdongle->lock_dongle);
	pthread_mutex_lock(&coder->sim->lock_sched);
	pthread_cond_broadcast(&coder->sim->cond_sched);
	pthread_mutex_unlock(&coder->sim->lock_sched);
}
