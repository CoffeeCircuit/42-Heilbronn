/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:09:23 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 19:28:26 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*dup;
	const char	*search_1;
	const char	*search_2;

	search_1 = s1;
	search_2 = s1;
	while (*search_2 != '\0')
		search_2++;
	while (ft_strchr(set, *search_1) != NULL)
		search_1++;
	while (ft_strchr(set, *search_2) != NULL && search_1 != search_2)
		search_2--;
	dup = ft_substr(s1, search_1 - s1, (search_2 - search_1) + 1);
	if (dup == NULL)
		return (NULL);
	return (dup);
}
