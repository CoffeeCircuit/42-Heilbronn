/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:52:42 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/14 16:16:35 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*r;
	size_t	index;

	index = 0;
	r = dest;
	if (dest != NULL || src != NULL)
	{
		while (n > index)
		{
			*(char *)dest = *(char *)src;
			src++;
			dest++;
			index++;
		}
	}
	return (r);
}
