/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_refactor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:12:05 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 08:23:22 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	refactor(t_coder *coder)
{
	if (found_stop(coder))
		return (0);
	log_action(coder, ACT_REFACTOR);
	usleep(coder->sim->time_to_refactor * 1000);
	return (1);
}
