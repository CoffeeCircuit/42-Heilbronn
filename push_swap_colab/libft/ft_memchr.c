/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:47:53 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/11 18:16:33 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	void			*tmp;
	unsigned char	target;

	target = c;
	while (0 < n)
	{
		if (*(unsigned char *)s == target)
		{
			tmp = (void *)s;
			return (tmp);
		}
		s++;
		n--;
	}
	return (NULL);
}
