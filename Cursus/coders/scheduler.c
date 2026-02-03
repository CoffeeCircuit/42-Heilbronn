/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:33:34 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 03:53:02 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*fifo_select(t_queue *queue)
{
	if (queue->qlength == 0)
		return (NULL);
	return (queue->entries[0].coder);
}

t_coder	*edf_select(t_queue *queue)
{
	int		best;
	long	best_deadline;
	long	dl;
	int		i;

	if (queue->qlength == 0)
		return (NULL);
	i = 1;
	best = 0;
	best_deadline = get_timestamp(&queue->entries[0].deadline);
	while (i < queue->qlength)
	{
		dl = get_timestamp(&queue->entries[i].deadline);
		if (dl < best_deadline)
		{
			best_deadline = dl;
			best = i;
		}
		i++;
	}
	return (queue->entries[best].coder);
}

t_coder	*scheduler_select(t_dongle *dongle)
{
	if (dongle->strat == FIFO)
		return (fifo_select(dongle->queue));
	else
		return (edf_select(dongle->queue));
}

void queue_push(t_queue *queue, t_coder *coder)
{
    t_qentry *e;

    if (queue->qlength >= queue->qcapacity)
        return;
    e = &queue->entries[queue->qlength++];
    e->coder = coder;
    gettimeofday(&e->requests, NULL);
    set_timeout_tv(&e->deadline, coder->sim->time_to_burnout);
}

void	queue_pop(t_queue *queue, t_coder *coder)
{
	int	i;

	i = 0;
	while (i < queue->qlength && queue->entries[i].coder != coder)
		i++;
	if (i == queue->qlength)
		return ;
	while (i + 1 < queue->qlength)
	{
		queue->entries[i] = queue->entries[i + 1];
		i++;
	}
	queue->qlength--;
}
