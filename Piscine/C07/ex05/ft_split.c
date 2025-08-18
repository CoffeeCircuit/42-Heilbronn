/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:33:00 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/13 14:42:37 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_is_in(char chr, char *charset)
{
	if (chr == *charset)
		return (1);
	if (*charset == '\0')
		return (0);
	return (ft_is_in(chr, charset + 1));
}

int	ft_word_count(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[++i])
	{
		if (str[i - 1] == str[i] && ft_is_in(str[i], charset))
			continue ;
		else if (ft_is_in(str[i - 1], charset) && ft_is_in(str[i], charset))
			continue ;
		else if (str[i - 1] != str[i] && ft_is_in(str[i - 1], charset))
			count++;
		else if (i - 1 == 0 && !(ft_is_in(str[i - 1], charset)))
			count++;
	}
	return (count);
}

char	*ft_get_word(char *str, char *charset, int *str_pos)
{
	int		index;
	char	buf[1024];
	char	*word;

	while ((ft_is_in(str[*str_pos], charset)))
		(*str_pos)++;
	index = 0;
	while (!(ft_is_in(str[*str_pos], charset)))
	{
		buf[index] = str[*str_pos];
		index++;
		(*str_pos)++;
	}
	word = (char *)malloc(index);
	word[index] = '\0';
	while (index)
	{
		word[index - 1] = buf[index - 1];
		index--;
	}
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**arr;
	int		index;
	int		arr_size;
	int		str_pos;

	str_pos = 0;
	index = 0;
	arr_size = ft_word_count(str, charset) + 1;
	arr = (char **)malloc(arr_size * sizeof(char *));
	arr[arr_size - 1] = NULL;
	while (index < arr_size - 1)
	{
		arr[index] = ft_get_word(str, charset, &str_pos);
		index++;
	}
	return (arr);
}
