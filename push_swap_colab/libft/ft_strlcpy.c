/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:26 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 14:38:09 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_strlen(const char *str);

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	ret_val;

	ret_val = ft_strlen(src);
	index = 0;
	if (size > 0)
	{
		while (index < size - 1 && src[index] != '\0')
		{
			dst[index] = src[index];
			index++;
		}
		if (dst[index] != '\0')
			dst[index] = '\0';
	}
	return (ret_val);
}
