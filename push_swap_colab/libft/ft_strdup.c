/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:45 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/12 17:34:20 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *str);

char	*ft_strdup(char *src)
{
	int		index;
	char	*duplicate;
	char	*duplicate_start;

	index = 0;
	duplicate = malloc(ft_strlen(src) + 1);
	duplicate_start = duplicate;
	if (duplicate == NULL)
		return (NULL);
	while (src[index] != '\0')
	{
		duplicate[index] = src[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate_start);
}
