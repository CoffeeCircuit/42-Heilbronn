/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:13:38 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/15 05:41:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_contains(char const *set, char c)
{
	int	contains;
	int	i;

	i = 0;
	contains = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			contains = 1;
			break ;
		}
		i++;
	}
	return (contains);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*str;
	char	*out;

	if (!s1 || !set)
		return (NULL);
	str = (char *)s1;
	while (*str && ft_contains(set, *str))
		str++;
	len = ft_strlen(str);
	while (ft_contains(set, str[len - 1]) && len > 0)
		len--;
	out = (char *)malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memmove(out, str, len);
	out[len] = '\0';
	return (out);
}
