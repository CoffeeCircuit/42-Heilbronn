/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 04:42:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 20:47:33 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	log_action(t_sim *sim, int coder_id, t_action action)
{
	long	timestamp;
	t_coder	*coder;

	coder = &sim->coders[coder_id];
	timestamp = get_timestamp(&sim->sim_start);
	pthread_mutex_lock(&sim->print_lock);
	if (action == COMPILE && !coder->sim->sim_stop)
		log_compile(coder, timestamp);
	else if (action == DEBUG && !coder->sim->sim_stop)
		log_debug(coder, timestamp);
	else if (action == REFACTOR && !coder->sim->sim_stop)
		log_refactor(coder, timestamp);
	else if (action == PICK_DONGLE && !coder->sim->sim_stop)
		log_pick_dongle(coder, timestamp);
	else if (action == BURNOUT && !coder->sim->sim_stop)
		log_burnout(coder, timestamp);
	else
	{
		pthread_mutex_unlock(&sim->print_lock);
		return ;
	}
	pthread_mutex_unlock(&sim->print_lock);
}
