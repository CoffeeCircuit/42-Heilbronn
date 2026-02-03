/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_coder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 04:11:21 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 23:36:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_stop(t_coder *coder, t_dongle *dongle)
{
	int		stop;
	t_sim	*sim;

	sim = coder->sim;
	pthread_mutex_lock(&sim->sim_stop_lock);
	stop = sim->sim_stop;
	pthread_mutex_unlock(&sim->sim_stop_lock);
	if (stop)
	{
		queue_pop(dongle->queue, coder);
		pthread_mutex_unlock(&dongle->dongle_lock);
		return (0);
	}
	return (1);
}

void	set_dongle_free(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->dongle_lock);
	dongle->is_free = 1;
	pthread_cond_broadcast(&dongle->free_cond);
	pthread_mutex_unlock(&dongle->dongle_lock);
	return ;
}

void	switch_dongles(t_dongle *first, t_dongle *second)
{
	t_dongle	*tmp;

	tmp = first;
	first = second;
	second = tmp;
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
		pthread_mutex_lock(&sim->sim_stop_lock);
		stop = sim->sim_stop;
		pthread_mutex_unlock(&sim->sim_stop_lock);
		if (stop)
			break ;
		compile(coder);
		pthread_mutex_lock(&sim->sim_stop_lock);
		stop = sim->sim_stop;
		pthread_mutex_unlock(&sim->sim_stop_lock);
		if (stop)
			break ;
		debug(coder);
		refactor(coder);
	}
	return (NULL);
}
