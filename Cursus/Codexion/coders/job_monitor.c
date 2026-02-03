/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 04:15:46 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 23:44:53 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <errno.h>

static int	found_burnout(t_coder *coders)
{
	int		i;
	long	elapsed;

	i = 0;
	while (i < coders[0].sim->number_of_coders)
	{
		pthread_mutex_lock(&coders[i].state_lock);
		if (coders[i].ts_comp_start.tv_sec != 0)
		{
			elapsed = get_timestamp(&coders[i].ts_comp_start);
			if (elapsed > coders[i].sim->time_to_burnout)
			{
				pthread_mutex_unlock(&coders[i].state_lock);
				coders->sim->sim_stop = 1;
				log_action(coders->sim, i, BURNOUT);
				pthread_cond_broadcast(&coders->sim->sim_stop_cond);
				return (i);
			}
		}
		pthread_mutex_unlock(&coders[i].state_lock);
		i++;
	}
	return (-1);
}

static int	reached_comp_count(t_coder *coders)
{
	int	i;

	i = 0;
	while (i < coders[0].sim->number_of_coders)
	{
		pthread_mutex_lock(&coders[i].state_lock);
		if (coders[i].compilations < coders[i].sim->number_of_compiles_required)
		{
			pthread_mutex_unlock(&coders[i].state_lock);
			return (0);
		}
		pthread_mutex_unlock(&coders[i].state_lock);
		i++;
	}
	coders->sim->sim_stop = 1;
	printf("Compilation finished\n");
	pthread_cond_broadcast(&coders->sim->sim_stop_cond);
	return (1);
}

void	*monitor_job(void *args)
{
	t_sim			*sim;
	int				retcode;
	struct timespec	timeout;

	retcode = 0;
	sim = (t_sim *)args;
	pthread_mutex_lock(&sim->sim_stop_lock);
	while (!sim->sim_stop)
	{
		set_timeout_ts(&timeout, 10);
		retcode = pthread_cond_timedwait(&sim->sim_stop_cond,
				&sim->sim_stop_lock, &timeout);
		if (retcode == ETIMEDOUT)
		{
			if (found_burnout(sim->coders) != -1)
				break ;
			if (reached_comp_count(sim->coders))
				break ;
		}
	}
	pthread_mutex_unlock(&sim->sim_stop_lock);
	return (NULL);
}
