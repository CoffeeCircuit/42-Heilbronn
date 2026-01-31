/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 03:48:44 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/31 23:19:13 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_TYPES_H
# define CODEXION_TYPES_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_coder	t_coder;

typedef enum e_action
{
	PICK_DONGLE,
	COMPILE,
	DEBUG,
	REFACTOR,
	BURNOUT,
}						t_action;

typedef enum e_strat
{
	FIFO,
	EDF
}						t_strat;

typedef enum e_coder_state
{
	OK,
	BURNED_OUT
}						t_coder_state;

typedef struct s_qentry
{
	t_coder				*coder;
	struct timeval		requests;
	struct timeval		deadline;
}						t_qentry;

typedef struct s_queue
{
	int					queue_length;
	int					queue_capacity;
	t_qentry			*entries;
}						t_queue;

typedef struct s_dongle
{
	int					id;
	int					cooldown_duration;
	t_strat				strat;
	t_queue				*queue;
	struct timeval		cooldown_end;
	pthread_cond_t		available;
	pthread_mutex_t		dongle_lock;
}						t_dongle;

typedef struct s_sim
{
	int					number_of_coders;
	int					time_to_burnout;
	int					time_to_compile;
	int					time_to_debug;
	int					time_to_refactor;
	int					number_of_compiles_required;
	int					dongle_cooldown;
	int					sim_stop;
	t_coder				*coders;
	t_dongle			*dongles;
	pthread_t			monitor;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		sim_stop_lock;
	struct timeval		sim_start;
	char 				scheduler[5];
}						t_sim;

typedef struct s_coder
{
	int					id;
	int					compilations;
	t_coder_state		state;
	t_dongle			*ldongle;
	t_dongle			*rdongle;
	pthread_t			job;
	struct timeval		ts_comp_start;
	struct timeval		ts_burnout;
	struct timeval		ts_debug;
	struct timeval		ts_refactor;
	struct timeval		ts_completion;
	t_sim				*sim;
}						t_coder;

#endif
