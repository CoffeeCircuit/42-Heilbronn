/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_coder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 04:11:21 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 04:02:36 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

static int	pick_dongle(t_coder *coder, t_dongle *dongle)
{
	t_sim	*sim;
	t_coder	*next;
	int		stop;

	sim = coder->sim;
	pthread_mutex_lock(&dongle->dongle_lock);
	queue_push(dongle->queue, coder);
	while (1)
	{
		pthread_mutex_lock(&sim->sim_stop_lock);
		stop = sim->sim_stop;
		pthread_mutex_unlock(&sim->sim_stop_lock);
		if (stop)
		{
			queue_pop(dongle->queue, coder);
			pthread_mutex_unlock(&dongle->dongle_lock);
			return (0);
		}
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

static void	compile(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	t_dongle	*tmp;

	first = coder->ldongle;
	second = coder->rdongle;
	if (first->id > second->id)
	{
		tmp = first;
		first = second;
		second = tmp;
	}
	if (!pick_dongle(coder, first))
		return ;
	if (!pick_dongle(coder, second))
	{
		release_dongle(first);
		return ;
	}
	pthread_mutex_lock(&coder->state_lock);
	gettimeofday(&coder->ts_comp_start, NULL);
	pthread_mutex_unlock(&coder->state_lock);
	pthread_mutex_lock(&coder->sim->print_lock);
	log_action(coder->sim, coder->id, COMPILE);
	pthread_mutex_unlock(&coder->sim->print_lock);
	usleep(coder->sim->time_to_compile * 1000);
	release_dongle(first);
	release_dongle(second);
}

static void	debug(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->print_lock);
	log_action(coder->sim, coder->id, DEBUG);
	pthread_mutex_unlock(&coder->sim->print_lock);
	usleep(coder->sim->time_to_debug * 1000);
}

static void	refactor(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->print_lock);
	log_action(coder->sim, coder->id, REFACTOR);
	pthread_mutex_unlock(&coder->sim->print_lock);
	usleep(coder->sim->time_to_refactor * 1000);
}

void	*coder_job(void *args)
{
	t_coder	*coder;
	t_sim	*sim;
	int		stop;

	coder = args;
	sim = coder->sim;
	while (1)
	{
		// Check if simulation should stop
		pthread_mutex_lock(&sim->sim_stop_lock);
		stop = sim->sim_stop;
		pthread_mutex_unlock(&sim->sim_stop_lock);
		if (stop)
			break ;
		compile(coder);
		debug(coder);
		refactor(coder);
	}
	return (NULL);
}
