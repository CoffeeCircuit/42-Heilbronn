/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cooldown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 08:38:28 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/14 07:50:38 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_cooldown(t_coder *coder, t_dongle *dongle)
{
	long			time_since_release;
	long			wait_ms;
	struct timespec	timeout;

	if (dongle->is_free)
	{
		time_since_release = get_timestamp(&dongle->ts_last_release);
		if (time_since_release >= dongle->cooldown)
		{
			if (scheduler_select(dongle->queue, coder->sim->scheduler) == coder)
				return (1);
			wait_ms = 1;
		}
		else
			wait_ms = dongle->cooldown - time_since_release;
	}
	else
		wait_ms = dongle->cooldown;
	if (wait_ms > 20)
		wait_ms = 20;
	if (wait_ms < 1)
		wait_ms = 1;
	set_delay_ts(&timeout, wait_ms);
	pthread_cond_timedwait(&dongle->cond_free, &dongle->lock_dongle, &timeout);
	return (0);
}
