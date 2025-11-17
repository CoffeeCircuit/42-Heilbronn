/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:33:15 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/11 18:58:37 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	void			*tmp;
	unsigned char	target;

	tmp = NULL;
	target = c;
	while (*s != '\0')
	{
		if (*s == target)
			tmp = (void *)s;
		s++;
	}
	if (*s == target)
		tmp = (void *)s;
	return ((char *)tmp);
}
