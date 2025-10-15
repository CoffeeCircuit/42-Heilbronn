/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:12:57 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/15 02:09:42 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	chr;

	len = ft_strlen(s);
	chr = (unsigned char)c;
	while (len >= 0)
	{
		if (s[len] == chr)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}
