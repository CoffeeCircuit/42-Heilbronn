/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:20:24 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/13 18:55:38 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	index;

	index = 0;
	while (index < n && src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	while (index < n)
	{
		dest[index] = '\0';
		index++;
	}
	return (dest);
}

char	*ft_strdup(char *src)
{
	char			*dup;
	unsigned int	src_len;

	dup = NULL;
	src_len = ft_strlen(src);
	dup = (char *)malloc((src_len + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strncpy(dup, src, src_len + 1);
	return (dup);
}
