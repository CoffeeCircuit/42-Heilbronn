/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:18:24 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/24 06:50:37 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*out;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	out = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, s1, s1_len);
	ft_memcpy(out + s1_len, s2, s2_len);
	out[s1_len + s2_len] = '\0';
	return (out);
}

char	*ft_strdup(const char *s)
{
	char	*out;

	out = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, s, ft_strlen(s));
	out[ft_strlen(s)] = '\0';
	return (out);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			size;
	size_t			i;
	unsigned char	chr;

	i = 0;
	size = ft_strlen(s) + 1;
	chr = (unsigned char)c;
	while (i < size)
	{
		if (s[i] == chr)
			return (&((char *)s)[i]);
		i++;
	}
	return (NULL);
}
