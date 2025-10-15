/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:19:27 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/13 11:53:19 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*cdest;
	const unsigned char	*csrc = (const unsigned char *)src;

	cdest = (unsigned char *)dest;
	if (cdest < csrc)
		while (n--)
			*cdest++ = *csrc++;
	else
	{
		cdest += n;
		csrc += n;
		while (n--)
			*(--cdest) = *(--csrc);
	}
	return (dest);
}
