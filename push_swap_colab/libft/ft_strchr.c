/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:28:01 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/11 18:56:47 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	void			*tmp;
	unsigned char	target;

	target = c;
	while (*s != '\0')
	{
		if (*s == target)
		{
			tmp = (void *)s;
			return (tmp);
		}
		s++;
	}
	if (*s == target)
	{
		tmp = (void *)s;
		return (tmp);
	}
	return (NULL);
}
