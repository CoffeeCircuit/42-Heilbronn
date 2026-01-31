/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 04:42:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/30 06:23:38 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion_logging.h"
#include <pthread.h>
#include <stdio.h>

void	log_action(t_sim *sim, int coder_id, t_action action)
{
	long	timestamp;
	t_coder	*coder;

	coder = &sim->coders[coder_id - 1];
	timestamp = get_timestamp(&sim->sim_start);
	pthread_mutex_lock(&sim->print_lock);
	if (action == COMPILE)
		log_compile(coder, timestamp);
	else if (action == DEBUG)
		log_debug(coder, timestamp);
	else if (action == REFACTOR)
		log_refactor(coder, timestamp);
	else if (action == PICK_DONGLE)
		log_pick_dongle(coder, timestamp);
	else if (action == BURNOUT)
		log_burnout(coder, timestamp);
	else
		fprintf(stderr, "Undefined action\n");
	pthread_mutex_unlock(&sim->print_lock);
}
