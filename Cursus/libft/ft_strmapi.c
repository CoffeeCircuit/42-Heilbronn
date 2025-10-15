/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:45:28 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/13 11:53:49 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	size_t			len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	out = (char *)malloc(len + 1);
	if (out == NULL)
		return (NULL);
	out[len] = '\0';
	while (s[i])
	{
		out[i] = f(i, s[i]);
		i++;
	}
	return (out);
}
