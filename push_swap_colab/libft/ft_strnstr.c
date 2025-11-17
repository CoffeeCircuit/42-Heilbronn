/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:01:05 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/12 17:31:12 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	smol_size;
	void	*r;

	smol_size = ft_strlen(little);
	if (smol_size == 0)
	{
		r = (void *)big;
		return (r);
	}
	while (*big != '\0' && len > 0)
	{
		if (smol_size > len)
			return (NULL);
		if (ft_strncmp(big, little, smol_size) == 0)
		{
			r = (void *)big;
			return (r);
		}
		big++;
		len--;
	}
	return (NULL);
}
