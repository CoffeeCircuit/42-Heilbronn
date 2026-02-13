/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 05:17:44 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/13 07:55:35 by abalcu           ###   ########.fr       */
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
	if (!pick_dongle(coder, coder->ldongle))
		return (0);
	if (!pick_dongle(coder, coder->rdongle))
		return (release_dongle(coder->ldongle), 0);
	log_action(coder, ACT_COMPILE);
	usleep(coder->sim->time_to_compile * 1000);
	gettimeofday(&coder->ts_comp_start, NULL);
	coder->number_of_compiles++;
	release_dongle(coder->ldongle);
	release_dongle(coder->rdongle);
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

static void	set_burnout(t_coder *coder)
{
	pthread_mutex_lock(&coder->sim->lock_sim);
	coder->sim->sim_stop = true;
	pthread_mutex_unlock(&coder->sim->lock_sim);
	pthread_mutex_lock(&coder->lock_state);
	coder->is_burntout = true;
	pthread_mutex_unlock(&coder->lock_state);
	log_action(coder, ACT_BURNOUT);
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
		{
			set_burnout(coder);
			break ;
		}
		if (compile(coder))
		{
			if (!debug(coder) || !refactor(coder))
				break ;
		}
	}
	return (NULL);
}
