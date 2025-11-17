/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:47:34 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/12 18:30:25 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*address;
	char	*start;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	address = malloc(len);
	if (address == NULL)
		return (NULL);
	start = address;
	while (*s1 != '\0')
	{
		*address = *s1;
		address++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*address = *s2;
		address++;
		s2++;
	}
	*address = '\0';
	return (start);
}
