/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:12:05 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/12 10:18:46 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	debug(t_coder *coder)
{
	if (found_stop(coder))
		return (0);
	log_action(coder, ACT_DEBUG);
	usleep(coder->sim->time_to_debug * 1000);
	return (1);
}
