/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:37:44 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/14 00:21:03 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (s1[index] == s2[index] && index < n)
	{
		if (s1[index] == '\0')
			return (0);
		index++;
	}
	if (s1[index] == '\0' && index < n)
		return (0 - (unsigned char)s2[index]);
	else if (s2[index] == '\0' && index < n)
		return ((unsigned char)s1[index]);
	else if (index < n)
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	else
		return (0);
}
