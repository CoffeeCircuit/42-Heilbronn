/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:17:23 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/30 06:05:36 by abalcu           ###   ########.fr       */
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
