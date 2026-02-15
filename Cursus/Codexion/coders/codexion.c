/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 04:50:29 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 12:23:47 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, const char **argv)
{
	t_sim	sim;
	void	*monitor_ret;
	int		i;

	if (!parse_arguments(argc, argv, &sim))
		return (print_help(stderr, "codexion"), EXIT_FAILURE);
	if (!sim_init(&sim))
		return (EXIT_FAILURE);
	if (pthread_create(&sim.job_monitor, NULL, job_monitor, &sim) != 0)
		return (sim_destroy(&sim), EXIT_FAILURE);
	if (coder_jobs_init(&sim) != 0)
		return (sim_destroy(&sim), EXIT_FAILURE);
	pthread_join(sim.job_monitor, &monitor_ret);
	i = 0;
	while (i < sim.number_of_coders)
	{
		pthread_join(sim.coders[i].job, NULL);
		i++;
	}
	if (monitor_ret == SIM_STOP || monitor_ret == SIM_STOP)
		return (sim_destroy(&sim), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
