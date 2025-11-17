/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:59:49 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 16:26:28 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int		ft_strlen(const char *str);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ret_val;

	if ((unsigned int)ft_strlen(dst) > size)
		ret_val = ft_strlen(src) + size;
	else
		ret_val = ft_strlen(src) + ft_strlen(dst);
	if (size > 0)
	{
		while (*dst != '\0')
		{
			dst++;
			size--;
			if (size <= 0)
				return (ret_val);
		}
		while (*src != '\0' && size > 1)
		{
			*dst = *src;
			dst++;
			src++;
			size--;
		}
		*dst = '\0';
	}
	return (ret_val);
}
