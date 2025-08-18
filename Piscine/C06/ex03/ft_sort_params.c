/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:41:08 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/10 20:32:24 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	ft_strcmp(char *s1, char *s2)
{
	int				index;
	unsigned char	s1_char;
	unsigned char	s2_char;

	index = 0;
	while (s1[index] || s2[index])
	{
		s1_char = s1[index];
		s2_char = s2[index];
		if (s1_char - s2_char != 0)
			return (s1_char - s2_char);
		index++;
	}
	return (0);
}

void	ft_sort_args(int argc, char **argv)
{
	int		pivot;
	int		index;
	char	*temp;

	pivot = 2;
	while (pivot < argc)
	{
		index = pivot;
		while (index > 0 && ft_strcmp(argv[index - 1], argv[index]) > 0)
		{
			temp = argv[index];
			argv[index] = argv[index - 1];
			argv[index - 1] = temp;
			index--;
		}
		pivot++;
	}
}

int	main(int argc, char **argv)
{
	int	index;

	index = 1;
	ft_sort_args(argc, argv);
	while (index < argc)
	{
		write(1, argv[index], ft_strlen(argv[index]));
		write(1, "\n", 1);
		index++;
	}
	return (0);
}
