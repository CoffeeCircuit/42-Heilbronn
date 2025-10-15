/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 04:18:03 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/15 00:59:18 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_list_len(char const *s, char c)
{
	int	in_substring;
	int	list_len;

	in_substring = 0;
	list_len = 0;
	while (*s != '\0')
	{
		if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			list_len++;
		}
		else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (list_len);
}

static size_t	ft_get_substr_len(char const *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

static char	**ft_safe_cpy(char **lst, char *str, size_t len, size_t i)
{
	lst[i] = (char *)malloc(len + 1);
	if (lst[i] == NULL)
	{
		while (i > 0)
			free(lst[--i]);
		free(lst);
		return (NULL);
	}
	else
		ft_memcpy(lst[i], str, len);
	return (lst);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**lst;
	size_t	i;
	size_t	lst_len;
	size_t	substr_len;

	i = 0;
	str = (char *)s;
	lst_len = ft_get_list_len(str, c);
	lst = (char **)malloc((lst_len + 1) * sizeof(char *));
	if (lst == NULL)
		return (NULL);
	lst[lst_len] = NULL;
	while (i < lst_len)
	{
		while (*str == c)
			str++;
		substr_len = ft_get_substr_len(str, c);
		if (!ft_safe_cpy(lst, str, substr_len, i))
			return (NULL);
		lst[i][substr_len] = '\0';
		str += substr_len;
		i++;
	}
	return (lst);
}
