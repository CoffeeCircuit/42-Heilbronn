/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 01:48:14 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/12 08:34:22 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	coder_mutex_cond_init(t_coder *coder)
{
	int	rc;

	coder->is_init = false;
	rc = pthread_mutex_init(&coder->lock_state, NULL);
	if (rc != 0)
		return (rc);
	rc = pthread_cond_init(&coder->cond_state, NULL);
	if (rc != 0)
	{
		pthread_mutex_destroy(&coder->lock_state);
		return (rc);
	}
	coder->is_init = true;
	return (0);
}

static void	coder_mutex_cond_destory(t_coder *coder)
{
	if (coder->is_init)
	{
		pthread_cond_destroy(&coder->cond_state);
		pthread_mutex_destroy(&coder->lock_state);
		coder->is_init = false;
	}
}

void	coders_destroy(t_coder *coders, int i)
{
	i--;
	while (i >= 0)
		coder_mutex_cond_destory(&coders[i--]);
	free(coders);
}

int	coders_init(t_sim *sim)
{
	int	i;

	i = 0;
	sim->coders = (t_coder *)malloc(sizeof(t_coder) * sim->number_of_coders);
	if (!sim->coders)
		return (0);
	while (i < sim->number_of_coders)
	{
		if (coder_mutex_cond_init(&sim->coders[i]) != 0)
			return (coders_destroy(sim->coders, i), 0);
		sim->coders[i].id = i;
		sim->coders[i].is_burntout = false;
		sim->coders[i].number_of_compiles = 0;
		sim->coders[i].ldongle = &sim->dongles[i];
		sim->coders[i].rdongle = &sim->dongles[(i + 1) % sim->number_of_coders];
		sim->coders[i].ts_comp_start = sim->sim_start;
		sim->coders[i].sim = sim;
		i++;
	}
	return (1);
}

int	coder_jobs_init(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->number_of_coders)
	{
		if (pthread_create(&sim->coders[i].job, NULL, job_coder,
				&sim->coders[i]) != 0)
			return (i);
		i++;
	}
	return (0);
}
