/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:41:28 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 17:23:21 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *str);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	index;

	index = 0;
	result = malloc(ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	result[ft_strlen(s)] = '\0';
	while (s[index] != '\0')
	{
		result[index] = (*f)(index, s[index]);
		index++;
	}
	return (result);
}
