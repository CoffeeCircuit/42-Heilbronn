/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:19:20 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/26 17:23:40 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = -1;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (d < s)
	{
		while (++i < n)
			d[i] = s[i];
	}
	else
	{
		while (n--)
			d[n] = s[n];
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dest;

	dest = (unsigned char *)s;
	while (n--)
		*dest++ = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	out = malloc(nmemb * size);
	if (out == NULL)
		return (NULL);
	ft_memset(out, 0, nmemb * size);
	return (out);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p = (const unsigned char *)s;
	unsigned char		target;

	target = (unsigned char)c;
	while (n--)
	{
		if (*p == target)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
