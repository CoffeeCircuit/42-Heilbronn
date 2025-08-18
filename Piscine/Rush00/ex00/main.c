/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:26:27 by jlayer            #+#    #+#             */
/*   Updated: 2025/08/03 21:18:39 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	g_symbols[8];
void	rush(int x, int y);
void	ft_putstr(char *str, int len);
void	ft_set_symbols(char *out_str, int rush_no);
void	ft_help(void);
void	ft_general(char **argv);
int		ft_is_eq(char *str1, char *str2, int length);
int		ft_atoi(char *str);

int	main(int argc, char **argv)
{
	if (argc == 1)
		ft_help();
	else if (argc == 2 && (ft_is_eq(argv[1], "-h", 2) == 1))
		ft_help();
	else if (argc == 2)
		ft_putstr("Error: Wrong argument\n", 22);
	else if (argc == 3)
	{
		if (ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1)
			ft_putstr("Error: Expected (positive) integers\n", 36);
		else
		{
			ft_set_symbols(g_symbols, 1);
			rush(ft_atoi(argv[1]), ft_atoi(argv[2]));
		}
	}
	else if (argc == 5 && (ft_is_eq(argv[3], "-r", 2) == 1))
	{
		ft_general(argv);
	}
	else
		ft_putstr("Error: Wrong argument\n", 22);
	return (0);
}

void	ft_help(void)
{
	ft_putstr("RUSH 01 - Piscine Aug 2025\n", 27);
	ft_putstr("   Draw rectangle to standard out\n", 34);
	ft_putstr("   Program accepts all versions of the Rush project\n", 52);
	ft_putstr("\n", 1);
	ft_putstr("USAGE\n", 6);
	ft_putstr("   ./a.out width height [-h] [-r]\n", 34);
	ft_putstr("Example\n", 8);
	ft_putstr("   ./a.out 5 2\n", 15);
	ft_putstr("   ./a.out 5 2 -r 2\n", 20);
	ft_putstr("   ./a.out -h\n", 14);
	ft_putstr("\n", 1);
	ft_putstr("OPTIONS\n", 8);
	ft_putstr("-r\n", 3);
	ft_putstr("    Select rush version, followed by a number 0..4\n", 51);
	ft_putstr("    If '-r' not provided, program defauls to the team's\n", 56);
	ft_putstr("    standard version (i.e. 1)\n", 30);
	ft_putstr("\n", 1);
	ft_putstr("-h\n", 3);
	ft_putstr("   Displays this help message\n", 30);
	ft_putstr("\n", 1);
}

// check for string equality
int	ft_is_eq(char *str1, char *str2, int length)
{
	int	index;

	index = 0;
	while (index <= length)
	{
		if (*str1 != *str2)
			return (0);
		str1++;
		str2++;
		index++;
	}
	return (1);
}

// converts str to int
// expected only positive values
// if negative values return -1 (error)
int	ft_atoi(char *str)
{
	unsigned int	result;

	result = 0;
	if (*str < '0' || *str > '9')
		return (-1);
	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	ft_general(char **argv)
{
	if (ft_atoi(argv[4]) == -1 || ft_atoi(argv[4]) > 4)
		ft_putstr("Error: Expected integer range 0..4 \n", 36);
	else
	{
		ft_set_symbols(g_symbols, ft_atoi(argv[4]));
		rush(ft_atoi(argv[1]), ft_atoi(argv[2]));
	}
}
