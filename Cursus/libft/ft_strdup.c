/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:51:59 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/13 11:53:36 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*out;

	out = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, s, ft_strlen(s));
	out[ft_strlen(s)] = '\0';
	return (out);
}
