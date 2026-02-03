/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_coder_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 04:11:21 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 23:37:06 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

static int	pick_dongle(t_coder *coder, t_dongle *dongle)
{
	t_coder	*next;

	pthread_mutex_lock(&dongle->dongle_lock);
	queue_push(dongle->queue, coder);
	while (1)
	{
		if (!check_stop(coder, dongle))
			return (0);
		next = scheduler_select(dongle);
		if (next == coder && dongle->is_free)
			break ;
		pthread_cond_wait(&dongle->free_cond, &dongle->dongle_lock);
	}
	dongle->is_free = 0;
	queue_pop(dongle->queue, coder);
	pthread_mutex_unlock(&dongle->dongle_lock);
	return (1);
}

static void	release_dongle(t_dongle *dongle)
{
	usleep(dongle->cooldown_duration * 1000);
	pthread_mutex_lock(&dongle->dongle_lock);
	dongle->is_free = 1;
	pthread_cond_broadcast(&dongle->free_cond);
	pthread_mutex_unlock(&dongle->dongle_lock);
}

void	compile(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = coder->ldongle;
	second = coder->rdongle;
	if (coder->id == coder->sim->number_of_coders - 1)
		switch_dongles(first, second);
	if (!pick_dongle(coder, first))
		return ;
	if (!pick_dongle(coder, second))
		return (set_dongle_free(first));
	pthread_mutex_lock(&coder->state_lock);
	gettimeofday(&coder->ts_comp_start, NULL);
	coder->compilations++;
	pthread_mutex_unlock(&coder->state_lock);
	log_action(coder->sim, coder->id, COMPILE);
	usleep(coder->sim->time_to_compile * 1000);
	pthread_mutex_lock(&coder->state_lock);
	coder->ts_comp_start = (struct timeval){0};
	pthread_mutex_unlock(&coder->state_lock);
	return (release_dongle(first), release_dongle(second));
}

void	debug(t_coder *coder)
{
	log_action(coder->sim, coder->id, DEBUG);
	usleep(coder->sim->time_to_debug * 1000);
}

void	refactor(t_coder *coder)
{
	log_action(coder->sim, coder->id, REFACTOR);
	usleep(coder->sim->time_to_refactor * 1000);
}
