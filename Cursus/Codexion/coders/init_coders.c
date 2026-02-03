/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 22:20:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	coder_mutex_init(void *ctx, int i)
{
	return (pthread_mutex_init(&((t_sim *)ctx)->coders[i].state_lock,
			NULL) == 0);
}

static int	coder_cond_init(void *ctx, int i)
{
	return (pthread_cond_init(&((t_sim *)ctx)->coders[i].state_cond,
			NULL) == 0);
}

static void	coder_mutex_cleanup(void *ctx, int i)
{
	pthread_mutex_destroy(&((t_sim *)ctx)->coders[i].state_lock);
}

static void	coder_cond_cleanup(void *ctx, int i)
{
	pthread_cond_destroy(&((t_sim *)ctx)->coders[i].state_cond);
}

int	init_coders(t_sim *sim)
{
	int				i;
	t_coder			*coders;
	static t_step	steps[] = {{coder_mutex_init, coder_mutex_cleanup},
	{coder_cond_init, coder_cond_cleanup}};

	if (!run_init_steps(sim, sim->number_of_coders, sizeof(steps)
			/ sizeof(steps[0]), steps))
		return (0);
	i = 0;
	coders = sim->coders;
	while (i < sim->number_of_coders)
	{
		coders[i].id = i;
		coders[i].compilations = 0;
		coders[i].state = OK;
		coders[i].ts_burnout = sim->sim_start;
		coders[i].ts_comp_start.tv_sec = 0;
		coders[i].ts_comp_start.tv_usec = 0;
		coders[i].ldongle = &sim->dongles[i];
		coders[i].rdongle = &sim->dongles[(i + 1) % sim->number_of_coders];
		coders[i].sim = sim;
		update_timeout(&coders[i].ts_burnout, sim->time_to_burnout);
		i++;
	}
	return (1);
}
