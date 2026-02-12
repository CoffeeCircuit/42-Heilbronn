/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 01:43:52 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/12 09:48:14 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_timestamp(struct timeval *start)
{
	struct timeval	now;
	long			elapsed_sec;
	long			elapsed_usec;

	gettimeofday(&now, NULL);
	elapsed_sec = (now.tv_sec - start->tv_sec);
	elapsed_usec = (now.tv_usec - start->tv_usec);
	if (elapsed_usec < 0)
	{
		elapsed_sec--;
		elapsed_usec += 1000000;
	}
	return (elapsed_sec * 1000 + elapsed_usec / 1000);
}

void	log_action(t_coder *coder, t_act action)
{
	struct timeval	*ts_start;
	const char		*action_str[] = {
		"%ld %d has taken a dongle\n",
		"%ld %d is compiling\n",
		"%ld %d is debugging\n",
		"%ld %d is refactoring\n",
		"%ld %d burned out\n",
		"%ld %d has finished\n",
	};

	ts_start = &coder->sim->sim_start;
	pthread_mutex_lock(&coder->sim->lock_print);
	printf(action_str[action], get_timestamp(ts_start), coder->id + 1);
	pthread_mutex_unlock(&coder->sim->lock_print);
}

void	pthread_print(t_sim *sim, char *msg)
{
	pthread_mutex_lock(&sim->lock_print);
	printf("%s\n", msg);
	pthread_mutex_unlock(&sim->lock_print);
}
