/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 04:30:26 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/15 10:28:50 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_valid_int(const char *str)
{
	long	nbr;

	if (strcmp(str, "0") == 0 || *str == '\0')
		return (0);
	nbr = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if (nbr > (INT_MAX - (*str - '0')) / 10)
			return (0);
		nbr = nbr * 10 + *str - '0';
		str++;
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

static int	validate_args(int argc, const char **argv)
{
	int	i;

	i = 1;
	if (argc < 2 || argc != 9)
	{
		fprintf(stderr, "Error: expected 8 arguments, got %d\n", argc - 1);
		return (0);
	}
	while (i < argc - 1)
	{
		if (!is_valid_int(argv[i]))
		{
			fprintf(stderr, "Error: argument "
				"%d ('%s') must be a positive integer\n", i, argv[i]);
			return (0);
		}
		i++;
	}
	if (!is_valid_scheduler(argv[argc - 1]))
	{
		fprintf(stderr, "Error: scheduler must be 'FIFO' or 'EDF', got '%s'\n",
			argv[argc - 1]);
		return (0);
	}
	return (1);
}

int	parse_arguments(int argc, const char **argv, t_sim *sim)
{
	if (!validate_args(argc, argv))
		return (0);
	sim->number_of_coders = atoi(argv[1]);
	if (sim->number_of_coders < 2)
	{
		fprintf(stderr, "Error: minimum 2 coders required\n");
		return (0);
	}
	sim->time_to_burnout = atoi(argv[2]);
	sim->time_to_compile = atoi(argv[3]);
	sim->time_to_debug = atoi(argv[4]);
	sim->time_to_refactor = atoi(argv[5]);
	sim->number_of_compiles_required = atoi(argv[6]);
	sim->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8], "FIFO") == 0)
		sim->scheduler = SCHEDULER_FIFO;
	if (strcmp(argv[8], "EDF") == 0)
		sim->scheduler = SCHEDULER_EDF;
	return (1);
}

void	print_help(FILE *stream, char *program)
{
	const char	*str = "\nUsage: ./%s ARGS...\n"
		"\n"
		"Arguments:\n"
		"  <number_of_coders>                Number of coders (>= 2)\n"
		"  <time_to_burnout>                 Time (in ms) to coder burnout\n"
		"  <time_to_compile>                 Time (in ms) to compile code\n"
		"  <time_to_debug>                   Time (in ms) to debug code\n"
		"  <time_to_refactor>                Time (in ms) to refactor code\n"
		"  <number_of_compiles_required>     Number of compilations before"
		" ending simulation\n"
		"  <dongle_cooldown>                 Time (in ms) for dongle cooldown\n"
		"  <scheduler>                       Scheduler type (FIFO | EDF)\n"
		"\n"
		"Observations:\n"
		"- All arguments are mandatory and must be positive integers.\n"
		"- The scheduler must be either 'FIFO' or 'EDF' (case insensitive).\n"
		"\n"
		"Example:\n"
		"  ./%s 10 400 100 100 100 5 10 FIFO\n";

	fprintf(stream, str, program, program);
}
