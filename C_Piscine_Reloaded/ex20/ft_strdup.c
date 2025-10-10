/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:19:16 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/10 11:48:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++ != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char *src)
{
	char	*out;
	int		i;
	int		slen;

	slen = ft_strlen(src);
	i = 0;
	out = (char *)malloc(sizeof(char) * (slen + 1));
	if (out == NULL)
		return (NULL);
	while (i < slen)
	{
		out[i] = src[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
