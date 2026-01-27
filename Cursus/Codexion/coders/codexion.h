/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:38:42 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/27 04:35:21 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef enum e_action
{
	TAKE_DONGLE,
	COMPILE,
	DEBUG,
	REFACTOR,
	BURNOUT,
	COMPILE_LIMIT_REACHED
}				t_action;

typedef struct s_args
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			compile_limit;
	int			dongle_cooldown;
	char		scheduler[5];
}				t_args;

void			print_help(FILE *stream, char *program_name);
int				parse_positional_args(int argc, char **argv, t_args *args);
int				is_positive_integer(const char *str);
int				is_valid_scheduler(const char *str);
int				validate_args(int argc, char **argv);
unsigned long	get_timestamp(void);
void			log_action(double timestamp, int coder_no, t_action action);

#endif /* CODEXION_H */
