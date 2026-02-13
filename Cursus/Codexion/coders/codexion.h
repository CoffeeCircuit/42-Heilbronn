/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 04:50:39 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/13 08:39:11 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif
# define SIM_STOP ((void *)1)
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct				s_coder;

typedef enum e_act
{
	ACT_DONGLE_PICK,
	ACT_COMPILE,
	ACT_DEBUG,
	ACT_REFACTOR,
	ACT_BURNOUT,
	ACT_FINISH,
}					t_act;

typedef enum e_scheduler
{
	SCHEDULER_FIFO,
	SCHEDULER_EDF
}					t_scheduler;

typedef struct s_qentry
{
	struct s_coder	*coder;
	long			ts_request;
	long			ts_deadline;
}					t_qentry;

typedef struct s_queue
{
	int				q_len;
	int				q_cap;
	t_qentry		*entries;
}					t_queue;

typedef struct s_dongle
{
	int				id;
	bool			is_init;
	bool			is_free;
	int				cooldown;
	struct timeval	ts_last_release;
	t_queue			*queue;
	pthread_mutex_t	lock_dongle;
	pthread_cond_t	cond_free;
}					t_dongle;

typedef struct s_sim
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
	bool			is_init;
	bool			sim_stop;
	char			*finished_coders;
	struct s_coder	*coders;
	t_dongle		*dongles;
	pthread_t		job_monitor;
	pthread_mutex_t	lock_print;
	pthread_mutex_t	lock_sim;
	pthread_cond_t	cond_sim;
	struct timeval	sim_start;
}					t_sim;

typedef struct s_coder
{
	int				id;
	int				number_of_compiles;
	bool			is_init;
	bool			is_burntout;
	t_dongle		*ldongle;
	t_dongle		*rdongle;
	pthread_t		job;
	pthread_mutex_t	lock_state;
	pthread_cond_t	cond_state;
	struct timeval	ts_comp_start;
	t_sim			*sim;
}					t_coder;

int					parse_arguments(int argc, const char **argv, t_sim *sim);
void				print_help(FILE *stream, char *program, char *err_msg);
long				get_timestamp(struct timeval *start);
void				log_action(t_coder *coder, t_act action);
void				pthread_print(t_sim *sim, char *msg);

void				sim_destroy(t_sim *sim);
int					sim_init(t_sim *sim);

void				coders_destroy(t_coder *coders, int i);
int					coders_init(t_sim *sim);
int					coder_jobs_init(t_sim *sim);
int					found_stop(t_coder *coder);
int					refactor(t_coder *coder);
int					debug(t_coder *coder);

int					check_cooldown(t_coder *coder, t_dongle *dongle);
void				dongles_destroy(t_dongle *dongles, int i);
int					dongles_init(t_sim *sim);

int					pick_dongle(t_coder *coder, t_dongle *dongle);
void				release_dongle(t_dongle *dongle);
t_coder				*scheduler_select(t_queue *q, t_scheduler type);

void				set_delay_ts(struct timespec *abstime, long delay_ms);
void				*job_monitor(void *args);
void				*job_coder(void *args);

#endif
