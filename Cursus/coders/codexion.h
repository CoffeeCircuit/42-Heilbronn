/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 06:27:35 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/04 00:11:18 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include "types.h"
# include <stdio.h>

int		parse_arguments(int argc, char **argv, t_sim *sim);
void	print_help(FILE *stream, char *program_name, char *error_msg);

int		run_init_steps(void *ctx, int count, int num_steps, t_step *steps);
int		init_queue(t_queue **qptr, int capacity);
int		init_dongles(t_sim *sim);
int		init_coders(t_sim *sim);

void	log_compile(t_coder *coder, long timestamp);
void	log_debug(t_coder *coder, long timestamp);
void	log_refactor(t_coder *coder, long timestamp);
void	log_pick_dongle(t_coder *coder, long timestamp);
void	log_burnout(t_coder *coder, long timestamp);
void	log_action(t_sim *sim, int coder_id, t_action action);

void	*monitor_job(void *args);
void	compile(t_coder *coder);
void	debug(t_coder *coder);
void	refactor(t_coder *coder);
int		check_stop(t_coder *coder, t_dongle *dongle);
void	set_dongle_free(t_dongle *dongle);
void	switch_dongles(t_dongle *first, t_dongle *second);

void	*coder_job(void *args);

long	get_timestamp(struct timeval *start);
void	set_timeout_ts(struct timespec *timeout, long duration_ms);
void	set_timeout_tv(struct timeval *timeout, long duration_ms);
void	update_timeout(struct timeval *last, long duration_ms);

void	queue_push(t_queue *queue, t_coder *coder);
void	queue_pop(t_queue *queue, t_coder *coder);
t_coder	*fifo_select(t_queue *queue);
t_coder	*edf_select(t_queue *queue);
t_coder	*scheduler_select(t_dongle *dongle);

void	destroy_sim(t_sim *sim);

#endif // CODEXION_H
