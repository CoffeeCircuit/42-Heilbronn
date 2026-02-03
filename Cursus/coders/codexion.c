/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:27:58 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 04:40:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdlib.h>

int	init_sim(t_sim *sim)
{
	sim->sim_stop = 0;
	sim->coders = NULL;
	sim->dongles = NULL;
	sim->init_flags = (t_init_flags){0};
	gettimeofday(&sim->sim_start, NULL);
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0
		|| pthread_mutex_init(&sim->sim_stop_lock, NULL) != 0
		|| pthread_cond_init(&sim->sim_stop_cond, NULL) != 0)
		return (destroy_sim(sim), 0);
	sim->coders = malloc(sim->number_of_coders * sizeof(t_coder));
	sim->dongles = malloc(sim->number_of_coders * sizeof(t_dongle));
	if (!sim->coders || !sim->dongles)
		return (destroy_sim(sim), 0);
	sim->init_flags.coders_allocated = sim->number_of_coders;
	sim->init_flags.dongles_allocated = sim->number_of_coders;
	if (!init_coders(sim) || !init_dongles(sim))
		return (destroy_sim(sim), 0);
	return (1);
}

void	join_threads(t_sim *sim)
{
	int	i;

	i = 0;
	if (sim->init_flags.monitor_created)
		pthread_join(sim->monitor, NULL);
	while (i < sim->init_flags.coder_threads_created)
	{
		pthread_join(sim->coders[i].job, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_sim	sim;

	if (!parse_arguments(argc, argv, &sim))
		return (print_help(stderr, "codexion"), EXIT_FAILURE);
	if (!init_sim(&sim))
		return (EXIT_FAILURE);
	if (pthread_create(&sim.monitor, NULL, monitor_job, &sim) != 0)
	{
		destroy_sim(&sim);
		return (EXIT_FAILURE);
	}
	i = 0;
	sim.init_flags.monitor_created = 1;
	while (i < sim.number_of_coders)
	{
		if (pthread_create(&sim.coders[i].job, NULL, coder_job,
				&sim.coders[i]) != 0)
			break ;
		sim.init_flags.coder_threads_created++;
		i++;
	}
	join_threads(&sim);
	destroy_sim(&sim);
	return (EXIT_SUCCESS);
}
