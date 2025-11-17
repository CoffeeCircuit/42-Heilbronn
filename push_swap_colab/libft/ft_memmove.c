/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:05:34 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/12 14:59:06 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static void	ft_h_copy_down(void *dest, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	src += n - 1;
	dest += n - 1;
	while (n > index)
	{
		*(char *)dest = *(char *)src;
		src--;
		dest--;
		index++;
	}
}

static void	ft_h_copy_up(void *dest, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	while (n > index)
	{
		*(char *)dest = *(char *)src;
		src++;
		dest++;
		index++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if ((dest - src) > 0)
		ft_h_copy_down(dest, src, n);
	else if ((dest - src) < 0)
		ft_h_copy_up(dest, src, n);
	return (dest);
}
