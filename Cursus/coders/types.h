/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 03:48:44 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/02 03:55:25 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include <pthread.h>
# include <sys/time.h>

typedef int				t_flag;
typedef int				(*t_init_fn)(void *ctx, int index);
typedef void			(*t_cleanup_fn)(void *ctx, int index);
typedef struct s_coder	t_coder;

typedef struct s_init_flags
{
	t_flag				coders_allocated;
	t_flag				dongles_allocated;
	t_flag				coder_mutexes;
	t_flag				coder_conds;
	t_flag				dongle_mutexes;
	t_flag				dongle_conds;
	t_flag				queues_initialized;
	t_flag				monitor_created;
	t_flag				coder_threads_created;
}						t_init_flags;

typedef struct s_step
{
	t_init_fn			init;
	t_cleanup_fn		cleanup;
}						t_step;

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
	int					qlength;
	int					qcapacity;
	t_qentry			*entries;
}						t_queue;

typedef struct s_dongle
{
	int					id;
	int					is_free;
	int					cooldown_duration;
	t_strat				strat;
	t_queue				*queue;
	struct timeval		cooldown_end;
	pthread_cond_t		free_cond;
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
	pthread_cond_t		sim_stop_cond;
	pthread_mutex_t		sim_stop_lock;
	struct timeval		sim_start;
	t_init_flags		init_flags;
	t_strat				scheduler;
}						t_sim;

typedef struct s_coder
{
	int					id;
	int					compilations;
	t_coder_state		state;
	t_dongle			*ldongle;
	t_dongle			*rdongle;
	pthread_t			job;
	pthread_mutex_t		state_lock;
	pthread_cond_t		state_cond;
	struct timeval		ts_comp_start;
	struct timeval		ts_burnout;
	struct timeval		ts_debug;
	struct timeval		ts_refactor;
	struct timeval		ts_completion;
	t_sim				*sim;
}						t_coder;

#endif
