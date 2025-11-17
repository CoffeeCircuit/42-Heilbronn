/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 15:26:20 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/14 15:50:08 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);

static void	*ft_h_cleanse_arr(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
	{
		free(arr[index]);
		index++;
	}
	free(arr);
	return (NULL);
}

static void	*ft_h_fill_arr(char **arr, char *s, int sub_num, char c)
{
	int	arr_index;
	int	index;
	int	forward_index;

	index = 0;
	arr_index = 0;
	while (s[index] == c && s[index] != '\0')
		index++;
	while (arr_index < sub_num && s[index] != '\0')
	{
		forward_index = index;
		while (s[forward_index] != c && s[forward_index] != '\0')
			forward_index++;
		arr[arr_index] = ft_substr(s, index, forward_index - index);
		if (arr[arr_index] == NULL)
			return (ft_h_cleanse_arr(arr));
		arr_index++;
		while (s[index] != c && s[index] != '\0')
			index++;
		while (s[index] == c && s[index] != '\0')
			index++;
	}
	arr[arr_index] = NULL;
	return (arr[0]);
}

char	**ft_split(char	const *s, char c)
{
	int		sub_num;
	char	**arr;
	int		iterator;
	void	*protector;

	sub_num = 0;
	iterator = 0;
	while (s[iterator] != '\0')
	{
		if (s[iterator] == c && iterator != 0)
			if (s[iterator - 1] != c)
				sub_num++;
		if (s[iterator] != c && s[iterator + 1] == '\0')
			sub_num++;
		iterator++;
	}
	arr = (char **)malloc(sizeof(char *) * (sub_num + 1));
	if (arr == NULL)
		return (NULL);
	protector = ft_h_fill_arr(arr, (char *)s, sub_num, c);
	if (protector == NULL && sub_num > 0)
		return (NULL);
	return (arr);
}
