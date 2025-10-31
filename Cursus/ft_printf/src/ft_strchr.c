/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:50:49 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/31 04:48:02 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

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
