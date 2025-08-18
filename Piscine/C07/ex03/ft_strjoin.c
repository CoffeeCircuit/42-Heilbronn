/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 16:54:02 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/15 20:01:02 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;
	if (src == NULL)
		return (dest);
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	return (dest);
}

int	ft_res_len(int size, char **strs, char *sep)
{
	int	res_len;
	int	l_index;

	l_index = 0;
	res_len = 0;
	while (size)
	{
		res_len += ft_strlen(strs[l_index]);
		if (size > 1)
			res_len += ft_strlen(sep);
		l_index++;
		size--;
	}
	return (res_len);
}

char	*ft_build_str(char **strs, char *sep, char *str, int lst_s)
{
	int	index;

	index = 0;
	while (index < lst_s)
	{
		ft_strcpy(str, strs[index]);
		str += ft_strlen(strs[index]);
		if (index < lst_s - 1)
		{
			ft_strcpy(str, sep);
			str += ft_strlen(sep);
		}
		index++;
	}
	return (str);
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*res;
	int		res_len;

	res = NULL;
	if (size <= 0)
	{
		res = (char *)malloc(sizeof(char));
		*res = '\0';
		return (res);
	}
	res_len = ft_res_len(size, strs, sep);
	res = (char *)malloc((res_len + 1) * sizeof(char));
	if (res_len == 0)
		*res = '\0';
	else
		res[res_len] = '\0';
	ft_build_str(strs, sep, res, size);
	return (res);
}
