/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:38:42 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/27 03:09:28 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef enum e_action
{
	TAKE_DONGLE,
	COMPILE,
	DEBUG,
	REFACTOR,
	BURNOUT,
	COMPILE_LIMIT_REACHED
}t_action;


typedef struct s_args
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	compile_limit;
	int dongle_cooldown;
	char	scheduler[5];
}	t_args;


#endif /* CODEXION_H */
