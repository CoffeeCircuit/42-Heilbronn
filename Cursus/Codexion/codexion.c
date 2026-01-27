/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:27:58 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/27 04:48:49 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

unsigned long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	log_action(double timestamp, int coder_no, t_action action)
{
	if (action == TAKE_DONGLE)
		printf("%.0f %d has taken dongle\n", timestamp, coder_no);
	else if (action == COMPILE)
		printf("%.0f %d is compiling\n", timestamp, coder_no);
	else if (action == DEBUG)
		printf("%.0f %d is debugging\n", timestamp, coder_no);
	else if (action == REFACTOR)
		printf("%.0f %d is refactoring\n", timestamp, coder_no);
	else if (action == BURNOUT)
		printf("%.0f %d burned out\n", timestamp, coder_no);
	else if (action == COMPILE_LIMIT_REACHED)
		printf("%.0f Reached compile limit\n", timestamp);
}

void	print_args(t_args *args)
{
	printf("Number of coders: %d\n", args->number_of_coders);
	printf("Time to burnout: %d ms\n", args->time_to_burnout);
	printf("Time to compile: %d ms\n", args->time_to_compile);
	printf("Time to debug: %d ms\n", args->time_to_debug);
	printf("Time to refactor: %d ms\n", args->time_to_refactor);
	printf("Compile limit: %d\n", args->compile_limit);
	printf("Dongle cooldown: %d ms\n", args->dongle_cooldown);
	printf("Scheduler: %s\n", args->scheduler);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (!validate_args(argc, argv) || !parse_positional_args(argc, argv, &args))
	{
		print_help(stderr, argv[0]);
		return (EXIT_FAILURE);
	}
	print_args(&args);
	return (EXIT_SUCCESS);
}
