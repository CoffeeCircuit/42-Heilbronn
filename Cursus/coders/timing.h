/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 05:25:00 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 03:00:38 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMING_H
# define TIMING_H
# include <sys/time.h>

long	get_timestamp(struct timeval *start);
void	set_timeout_ts(struct timespec *timeout, long duration_ms);
void	set_timeout_tv(struct timeval *timeout, long duration_ms);
void	update_timeout(struct timeval *last, long duration_ms);

#endif
