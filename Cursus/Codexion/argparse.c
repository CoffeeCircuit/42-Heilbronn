/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 04:30:26 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/31 23:57:50 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	is_positive_integer(const char *str)
{
	int		i;
	long	nbr;

	if (strcmp(str, "0") == 0 || *str == '\0')
		return (0);
	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (nbr > (INT_MAX - (str[i] - '0')) / 10)
			return (0);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (1);
}

static int	is_valid_scheduler(const char *str)
{
	int		len;
	char	buf[5];

	if (strlen(str) > 4)
		return (0);
	len = 0;
	while (str[len] && len < 5)
	{
		buf[len] = str[len] & ~32;
		len++;
	}
	buf[len] = '\0';
	if (len == 4 && strcmp(buf, "FIFO") == 0)
		return (1);
	if (len == 3 && strcmp(buf, "EDF") == 0)
		return (1);
	return (0);
}

static int	validate_args(int argc, char **argv)
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

int	parse_arguments(int argc, char **argv, t_sim *sim)
{
	int	i;

	if (!validate_args(argc, argv))
		return (0);
	sim->number_of_coders = atoi(argv[1]);
	sim->time_to_burnout = atoi(argv[2]);
	sim->time_to_compile = atoi(argv[3]);
	sim->time_to_debug = atoi(argv[4]);
	sim->time_to_refactor = atoi(argv[5]);
	sim->number_of_compiles_required = atoi(argv[6]);
	sim->dongle_cooldown = atoi(argv[7]);
	i = -1;
	while (++i < 4)
		sim->scheduler[i] = argv[8][i];
	sim->scheduler[4] = '\0';
	return (1);
}

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

	fprintf(stream, str, program_name, program_name);
}
