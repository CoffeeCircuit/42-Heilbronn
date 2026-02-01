/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 04:15:46 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 04:16:45 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <errno.h>

void	*monitor_job(void *args)
{
	t_sim *sim;
	int coder_i;
	int retcode;
	struct timespec timeout;
	struct timeval timestamp;

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
			coder_i = found_burnout(sim->coders); // TODO implementation
			if (coder_i != -1)
			{
				sim->sim_stop = 1;
				log_burnout(&sim->coders[coder_i], get_timestamp(&timestamp));
					// TODO make get_timestamp to refence sim.start
				pthread_cond_broadcast(&sim->sim_stop_cond);
				break ;
			}
			if (reached_comp_count(sim->coders)) // TODO implementation
			{
				sim->sim_stop = 1;
				printf("Compilation finished\n");
				pthread_cond_broadcast(&sim->sim_stop_cond);
				break ;
			}
		}
	}
	pthread_mutex_unlock(&sim->sim_stop_lock);
	return (NULL);
} // TODO break in multiple functions
