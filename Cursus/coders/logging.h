/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:25:18 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 03:00:29 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H
# include "types.h"

void	log_compile(t_coder *coder, long timestamp);
void	log_debug(t_coder *coder, long timestamp);
void	log_refactor(t_coder *coder, long timestamp);
void	log_pick_dongle(t_coder *coder, long timestamp);
void	log_burnout(t_coder *coder, long timestamp);

void	log_action(t_sim *sim, int coder_id, t_action action);

#endif
