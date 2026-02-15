/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 11:12:33 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 11:48:49 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	queue_push(t_queue *q, t_coder *coder)
{
	long	now_ms;

	if (q->q_len >= q->q_cap)
		return ;
	q->entries[q->q_len].coder = coder;
	now_ms = get_timestamp(&coder->sim->sim_start);
	q->entries[q->q_len].ts_request = now_ms;
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

static t_coder	*edf_scheduler(t_queue *q)
{
	int		i;
	int		e_idx;
	long	e_deadline;

	e_idx = -1;
	e_deadline = LONG_MAX;
	i = 0;
	while (i < q->q_len)
	{
		if (dongles_available(q->entries[i].coder))
		{
			if (e_idx == -1 || q->entries[i].ts_deadline < e_deadline
				|| (q->entries[i].ts_deadline == e_deadline
					&& q->entries[i].coder->id > q->entries[e_idx].coder->id))
			{
				e_deadline = q->entries[i].ts_deadline;
				e_idx = i;
			}
		}
		i++;
	}
	if (e_idx == -1)
		return (NULL);
	return (q->entries[e_idx].coder);
}

t_coder	*scheduler_select(t_queue *q, t_scheduler type)
{
	int	i;

	if (q->q_len == 0)
		return (NULL);
	if (type == SCHEDULER_FIFO)
	{
		i = 0;
		while (i < q->q_len)
		{
			if (dongles_available(q->entries[i].coder))
				return (q->entries[i].coder);
			i++;
		}
		return (NULL);
	}
	if (type == SCHEDULER_EDF)
		return (edf_scheduler(q));
	return (NULL);
}
