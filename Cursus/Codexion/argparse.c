/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 04:30:26 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/27 04:47:14 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_help(FILE *stream, char *program_name)
{
	const char	*str = "Usage: %s ARGS...\n"
		"\n"
		"Arguments:\n"
		"  <number_of_coders>      Number of coders\n"
		"  <time_to_burnout>       Time (in ms) to coder burns out\n"
		"  <time_to_compile>       Time (in ms) to compile code\n"
		"  <time_to_debug>         Time (in ms) to debug code\n"
		"  <time_to_refactor>      Time (in ms) to refactor code\n"
		"  <compile_limit>         Number of compilations before ending"
		" simulation\n"
		"  <dongle_cooldown>       Time (in ms) for dongle cooldown\n"
		"  <scheduler>             Scheduler type (FIFO | EDF)\n"
		"\n"
		"Observations:\n"
		"- All arguments are mandatory and must be positive integers.\n"
		"- The scheduler must be either 'FIFO' or 'EDF' (case insensitive).\n"
		"\n"
		"Example:\n"
		"  %s 5 800 200 100 150 10 50 FIFO\n";

	fprintf(stream, str, program_name, program_name, program_name);
}

int	parse_positional_args(int argc, char **argv, t_args *args)
{
	if (argc < 8)
		return (0);
	args->number_of_coders = atoi(argv[1]);
	args->time_to_burnout = atoi(argv[2]);
	args->time_to_compile = atoi(argv[3]);
	args->time_to_debug = atoi(argv[4]);
	args->time_to_refactor = atoi(argv[5]);
	args->compile_limit = atoi(argv[6]);
	args->dongle_cooldown = atoi(argv[7]);
	strncpy(args->scheduler, argv[8], 4);
	args->scheduler[4] = '\0';
	return (1);
}

int	is_positive_integer(const char *str)
{
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_scheduler(const char *str)
{
	int		i;
	char	lower_str[5];

	i = 0;
	while (str[i] && i < 4)
	{
		lower_str[i] = str[i] & ~32;
		i++;
	}
	lower_str[i] = '\0';
	return (strcmp(lower_str, "FIFO") == 0 || strcmp(lower_str, "EDF") == 0);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 2 || argc != 9)
		return (0);
	while (i < argc - 1)
		if (!is_positive_integer(argv[i++]))
			return (0);
	if (!is_valid_scheduler(argv[argc - 1]))
		return (0);
	return (1);
}
