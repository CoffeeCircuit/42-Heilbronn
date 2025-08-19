/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:39:04 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/19 13:22:48 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	index;

	if (str == NULL)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strdup(char *src)
{
	char	*dup;
	int		src_len;
	int		index;

	if (src == NULL)
		return (NULL);
	index = 0;
	src_len = ft_strlen(src);
	dup = (char *)malloc((src_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (src[index])
	{
		dup[index] = src[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	t_stock_str	*str_list;
	int			index;

	if (ac < 0)
		return (NULL);
	index = 0;
	str_list = (t_stock_str *)malloc((ac + 1) * sizeof(t_stock_str));
	if (str_list == NULL)
		return (NULL);
	while (index < ac)
	{
		str_list[index].size = ft_strlen(av[index]);
		str_list[index].str = av[index];
		str_list[index].copy = ft_strdup(av[index]);
		index++;
	}
	str_list[index].str = 0;
	return (str_list);
}
