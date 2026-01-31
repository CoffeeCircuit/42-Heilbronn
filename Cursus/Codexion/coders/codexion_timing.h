/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_timing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:25:00 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/31 22:54:43 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_TIMING_H
# define CODEXION_TIMING_H
# include <sys/time.h>

long	get_timestmap(struct timeval *start);
void	set_timeout(struct timespec *timeout, long duration_ms);

#endif
