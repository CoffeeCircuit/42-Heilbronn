/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:17:56 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/10 10:54:43 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(int c);

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
	int	len;

	index = 1;
	ft_sort_args(argc, argv);
	while (index < argc)
	{
		len = ft_strlen(argv[index]);
		while (len--)
		{
			ft_putchar(*argv[index]);
			argv[index]++;
		}
		ft_putchar('\n');
		index++;
	}
	return (0);
}
