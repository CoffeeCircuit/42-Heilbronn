/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:48:54 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/15 00:29:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*cs;
	unsigned char	chr;

	i = 0;
	cs = (unsigned char *)s;
	chr = (unsigned char)c;
	while (i < n)
	{
		if (cs[i] == chr)
			return ((void *)&cs[i]);
		i++;
	}
	return (NULL);
}
