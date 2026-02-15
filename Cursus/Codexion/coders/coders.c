/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 05:17:44 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 12:15:46 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	compile(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	if (coder->is_burntout
		|| coder->number_of_compiles >= sim->number_of_compiles_required)
		return (0);
	if (!pick_dongles(coder))
		return (0);
	gettimeofday(&coder->ts_comp_start, NULL);
	log_action(coder, ACT_COMPILE);
	usleep(coder->sim->time_to_compile * 1000);
	coder->number_of_compiles++;
	release_dongles(coder);
	return (1);
}

static void	set_stop(t_coder *coder, bool *stop, bool *finished)
{
	int		i;
	t_sim	*sim;

	sim = coder->sim;
	i = 0;
	pthread_mutex_lock(&sim->lock_sim);
	if (sim->sim_stop)
		*stop = true;
	else if (*stop)
		sim->sim_stop = true;
	if (*finished)
	{
		while (&sim->coders[i] != coder)
			i++;
		sim->finished_coders[i] = 1;
	}
	pthread_mutex_unlock(&sim->lock_sim);
}

static void	set_burnout(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->lock_sim);
	coder->sim->sim_stop = true;
	pthread_cond_broadcast(&coder->sim->cond_sim);
	pthread_mutex_unlock(&coder->sim->lock_sim);
	pthread_mutex_lock(&coder->lock_state);
	coder->is_burntout = true;
	pthread_mutex_unlock(&coder->lock_state);
	pthread_mutex_lock(&coder->sim->lock_sched);
	pthread_cond_broadcast(&coder->sim->cond_sched);
	pthread_mutex_unlock(&coder->sim->lock_sched);
	log_action(coder, ACT_BURNOUT);
}

int	found_stop(t_coder *coder)
{
	t_sim	*sim;
	bool	stop;
	bool	finished;

	sim = coder->sim;
	finished = false;
	pthread_mutex_lock(&coder->lock_state);
	stop = coder->is_burntout;
	if (!stop && coder->number_of_compiles >= sim->number_of_compiles_required)
		finished = true;
	pthread_mutex_unlock(&coder->lock_state);
	set_stop(coder, &stop, &finished);
	if (stop || finished)
		return (1);
	return (0);
}

void	*job_coder(void *args)
{
	t_coder	*coder;
	long	tdelta;

	coder = (t_coder *)args;
	while (true)
	{
		if (found_stop(coder))
			break ;
		tdelta = get_timestamp(&coder->ts_comp_start);
		if (tdelta >= coder->sim->time_to_burnout)
			return (set_burnout(coder), NULL);
		if (compile(coder))
		{
			if (!debug(coder) || !refactor(coder))
				break ;
		}
		else
		{
			if (get_timestamp(&coder->ts_comp_start)
				&& tdelta >= coder->sim->time_to_burnout)
				set_burnout(coder);
			break ;
		}
	}
	return (NULL);
}
