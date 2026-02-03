/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_queue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:53:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 04:43:24 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

int	init_queue(t_queue **qptr, int capacity)
{
	t_queue	*queue;

	*qptr = NULL;
	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (0);
	queue->qlength = 0;
	queue->qcapacity = capacity;
	queue->entries = malloc(sizeof(t_qentry) * capacity);
	if (!queue->entries)
	{
		free(queue);
		*qptr = NULL;
		return (0);
	}
	*qptr = queue;
	return (1);
}
