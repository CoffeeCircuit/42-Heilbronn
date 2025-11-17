/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:19:06 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/15 15:45:29 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_strdup(char *src);

static void	ft_h_fill_sub(char *sub, char const *s, size_t sub_len)
{
	while (--sub_len > 0)
	{
		*sub = *s;
		sub++;
		s++;
	}
	*sub = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	size_t	s_len;
	char	*sub;

	s_len = ft_strlen(s);
	if (start > s_len || len < 1)
		return (ft_strdup(""));
	s_len -= start;
	if (len > s_len)
		sub_len = s_len + 1;
	else
		sub_len = len + 1;
	sub = malloc(sub_len);
	if (sub == NULL)
		return (NULL);
	start++;
	while (--start > 0)
		s++;
	ft_h_fill_sub(sub, s, sub_len);
	return (sub);
}

// void	main(void)
// {
// 	ft_substr("", 0, 0);
// }
