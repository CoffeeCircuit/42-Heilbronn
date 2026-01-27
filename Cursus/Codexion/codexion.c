/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:27:58 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/27 04:19:08 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


unsigned long get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void log_action(double timestamp, int coder_no, t_action action)
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

void print_help(FILE* stream, char *program_name)
{
	const char *str = "Usage: %s ARGS...\n"
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
		"  -h                         Display this help message\n"
		"\n"
		"Observations:\n"
		" - All arguments are mandatory and must be positive integers.\n"
		" - The scheduler must be either 'FIFO' or 'EDF' (case insensitive).\n"
		"\n"
		"Example:\n"
		"  %s 5 800 200 100 150 10 50 FIFO\n";
	
	fprintf(stream, str, program_name, program_name, program_name);
}

void print_args(t_args *args)
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

int parse_positional_args(int argc, char **argv, t_args *args)
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

int is_positive_integer(const char *str)
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

int is_valid_scheduler(const char *str)
{
	int i = 0;
	char lower_str[5];
	while (str[i] && i < 4)
	{
		lower_str[i] = str[i] & ~32;
		i++;	
	}
	lower_str[i] = '\0';
	return (strcmp(lower_str, "FIFO") == 0 || strcmp(lower_str, "EDF") == 0);
}

int validate_args(int argc, char **argv)
{
	
	if (argc == 2 && strcmp(argv[1], "-h") == 0)
	{
		print_help(stdout, argv[0]);
		exit(EXIT_SUCCESS);
	}
	
	if (argc < 2 || argc != 9)
	{
		fprintf(stderr, "Error: Invalid number of arguments.\n");
		return (0);
	}
	
	int i = 1;
	while (i < argc - 1)
		if (!is_positive_integer(argv[i++]))
		{
			fprintf(stderr, "Error: Invalid argument %s.\n", argv[i - 1]);
			return (0);
		}

	if (!is_valid_scheduler(argv[argc - 1]))
	{
		fprintf(stderr, "Error: Invalid scheduler type (FIFO | EDF).\n");
		return (0);
	}
	
	return (1);
}




int main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (EXIT_FAILURE);
	
	t_args args;
	if (!parse_positional_args(argc, argv, &args))
		return (EXIT_FAILURE);

	
	print_args(&args);
	
	

	
	return (EXIT_SUCCESS);
}
