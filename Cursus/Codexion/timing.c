/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:17:23 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/31 22:51:26 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion_timing.h"
#include <stddef.h>
#include <sys/time.h>

long	get_timestmap(struct timeval *start)
{
	struct timeval	now;
	long			delta_sec;
	long			delta_usec;

	gettimeofday(&now, NULL);
	delta_sec = now.tv_sec - start->tv_sec;
	delta_usec = now.tv_usec - start->tv_usec;
	if (delta_usec < 0)
	{
		delta_sec -= 1;
		delta_usec += 1000000;
	}
	return (delta_sec * 1000 + delta_usec / 1000);
}

void	set_timeout(struct timespec *timeout, long duration_ms)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	timeout->tv_sec = now.tv_sec + duration_ms / 1000;
	timeout->tv_nsec = now.tv_usec * 1000 + (duration_ms % 1000) * 1000000;
	if (timeout->tv_nsec >= 1000000000)
	{
		timeout->tv_sec += 1;
		timeout->tv_nsec -= 1000000000;
	}
}
