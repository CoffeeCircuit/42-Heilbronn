/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:38:40 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/14 12:11:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

void	ft_set_lookup(int *lu_table, char *base, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		lu_table[index] = -1;
		index++;
	}
	index = 0;
	while (index < ft_strlen(base))
	{
		lu_table[(int)base[index]] = index;
		index++;
	}
}

int	ft_is_valid_base(int *lu_table, char *base, int size)
{
	int	index;

	index = 0;
	if (ft_strlen(base) <= 1)
		return (0);
	ft_set_lookup(lu_table, base, size);
	while (base[index])
	{
		if (lu_table[(int)base[index]] == -1)
			return (0);
		index++;
	}
	return (1);
}

int	ft_in_base(char chr, char *base)
{
	int	index;

	index = 0;
	while (base[index])
	{
		if (chr == base[index])
			return (1);
		index++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int		result;
	int		index;
	char	negation;
	int		lu_table[256];

	index = 0;
	negation = 0;
	result = 0;
	if (ft_is_valid_base(lu_table, base, sizeof(lu_table) / sizeof(int)))
	{
		while ((str[index] >= '\t' && str[index] <= '\r') || str[index] == ' ')
			index++;
		while (str[index] == '+' || str[index] == '-')
		{
			if (str[index] == '-')
				negation++;
			index++;
		}
		while (ft_in_base(str[index], base))
		{
			result = result * ft_strlen(base) + lu_table[(int)str[index]];
			index++;
		}
	}
	return (result * (1 - 2 * (~(negation % 2) ^ -1)));
}
