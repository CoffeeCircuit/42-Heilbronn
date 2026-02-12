/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 03:18:44 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/12 10:40:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_delay_ts(struct timespec *abstime, long delay_ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	abstime->tv_sec = now.tv_sec + delay_ms / 1000;
	abstime->tv_nsec = now.tv_usec * 1000 + (delay_ms % 1000) * 1000000;
	if (abstime->tv_nsec >= 1000000000L)
	{
		abstime->tv_sec += 1;
		abstime->tv_nsec -= 1000000000L;
	}
}

static int	count_finished(char *finished_coders, int n)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < n)
	{
		if (finished_coders[i])
			count++;
		i++;
	}
	return (count);
}

void	*job_monitor(void *args)
{
	t_sim			*sim;
	int				stopped;
	int				all_finished;
	struct timespec	delay;

	sim = (t_sim *)args;
	pthread_mutex_lock(&sim->lock_sim);
	while (!sim->sim_stop && count_finished(sim->finished_coders,
			sim->number_of_coders) < sim->number_of_coders)
	{
		set_delay_ts(&delay, 10);
		pthread_cond_timedwait(&sim->cond_sim, &sim->lock_sim, &delay);
	}
	stopped = sim->sim_stop;
	all_finished = count_finished(sim->finished_coders,
			sim->number_of_coders) >= sim->number_of_coders;
	pthread_mutex_unlock(&sim->lock_sim);
	if (stopped)
		return (SIM_STOP);
	if (all_finished)
	{
		pthread_print(sim, "All coders finished.");
		return (SIM_STOP);
	}
	return (NULL);
}
