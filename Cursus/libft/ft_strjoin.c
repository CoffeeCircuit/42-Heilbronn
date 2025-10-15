/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:53:26 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/13 11:53:40 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*out;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	out = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, s1, s1_len);
	ft_memcpy(out + s1_len, s2, s2_len);
	out[s1_len + s2_len] = '\0';
	return (out);
}
