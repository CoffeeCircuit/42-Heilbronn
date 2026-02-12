/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 05:31:31 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/12 09:53:23 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	queue_push(t_queue *q, t_coder *coder)
{
	if (q->q_len >= q->q_cap)
		return ;
	q->entries[q->q_len].coder = coder;
	q->entries[q->q_len].ts_request = get_timestamp(&coder->sim->sim_start);
	q->entries[q->q_len].ts_deadline = get_timestamp(&coder->ts_comp_start)
		+ coder->sim->time_to_burnout;
	q->q_len++;
}

void	queue_pop(t_queue *q, t_coder *coder)
{
	int	i;

	i = 0;
	while (q->entries[i].coder != coder && i < q->q_len)
		i++;
	if (i == q->q_len)
		return ;
	while (i < q->q_len - 1)
	{
		q->entries[i] = q->entries[i + 1];
		i++;
	}
	q->q_len--;
}

t_coder	*scheduler_select(t_queue *q, t_scheduler type)
{
	int		i;
	int		earliest_idx;
	long	earliest_deadline;

	if (q->q_len == 0)
		return (NULL);
	if (type == SCHEDULER_FIFO)
		return (q->entries[0].coder);
	if (type == SCHEDULER_EDF)
	{
		i = 1;
		earliest_idx = 0;
		earliest_deadline = q->entries[0].ts_deadline;
		while (i < q->q_len)
		{
			if (q->entries[i].ts_deadline < earliest_deadline)
			{
				earliest_deadline = q->entries[i].ts_deadline;
				earliest_idx = i;
			}
			i++;
		}
		return (q->entries[earliest_idx].coder);
	}
	return (NULL);
}

int	pick_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock_dongle);
	queue_push(dongle->queue, coder);
	while (true)
	{
		pthread_mutex_lock(&coder->sim->lock_sim);
		if (coder->sim->sim_stop)
		{
			pthread_mutex_unlock(&coder->sim->lock_sim);
			queue_pop(dongle->queue, coder);
			pthread_mutex_unlock(&dongle->lock_dongle);
			return (0);
		}
		pthread_mutex_unlock(&coder->sim->lock_sim);
		if (dongle->is_free)
		{
			if (scheduler_select(dongle->queue, coder->sim->scheduler) == coder)
				break ;
		}
		pthread_cond_wait(&dongle->cond_free, &dongle->lock_dongle);
	}
	dongle->is_free = false;
	queue_pop(dongle->queue, coder);
	pthread_mutex_unlock(&dongle->lock_dongle);
	return (1);
}

void	release_dongle(t_dongle *dongle)
{
	usleep(dongle->cooldown * 1000);
	pthread_mutex_lock(&dongle->lock_dongle);
	dongle->is_free = true;
	pthread_cond_broadcast(&dongle->cond_free);
	pthread_mutex_unlock(&dongle->lock_dongle);
}
