/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 04:42:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/03 04:36:43 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	log_compile(t_coder *coder, long timestamp)
{
	printf("%ld %d is compiling\n", timestamp, coder->id);
	fflush(stdout);
}

void	log_debug(t_coder *coder, long timestamp)
{
	printf("%ld %d is debugging\n", timestamp, coder->id);
	fflush(stdout);
}

void	log_refactor(t_coder *coder, long timestamp)
{
	printf("%ld %d is refactoring\n", timestamp, coder->id);
	fflush(stdout);
}

void	log_pick_dongle(t_coder *coder, long timestamp)
{
	printf("%ld %d has taken a dongle\n", timestamp, coder->id);
}

void	log_burnout(t_coder *coder, long timestamp)
{
	printf("%ld %d burned out\n", timestamp, coder->id);
}
