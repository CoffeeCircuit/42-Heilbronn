/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:43:33 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/09 13:29:48 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlen(char *str)
{
	int				index;
	unsigned int	len;

	len = 0;
	index = 0;
	while (str[index])
	{
		len++;
		index++;
	}
	return (len);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	index_src;
	unsigned int	index_dst;
	unsigned int	len;

	len = ft_strlen(dest) + ft_strlen(src);
	index_src = 0;
	index_dst = 0;
	while (dest[index_dst])
		index_dst++;
	while (src[index_src] && ft_strlen(src) < size - 1 && index_dst < size - 1)
	{
		dest[index_dst] = src[index_src];
		index_dst++;
		index_src++;
	}
	while (index_src < size && index_dst < size - 1)
	{
		dest[index_dst] = '\0';
		index_dst++;
		index_src++;
	}
	return (len);
}

// #include <bsd/string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char dst[10];
// 	char src[20];
// 	strncpy(src, "t" , sizeof(src));
// 	strncpy(dst, "test" , sizeof(dst));
// 	printf("dst: '%s', src: '%s'\n", dst, src);
// 	printf("strlcat   : %ld, %s\n", strlcat(dst, src, sizeof(dst)), dst);
// 	strncpy(dst, "test" , sizeof(dst));
// 	printf("ft_strlcat: %ld, %s\n\n", ft_strlcat(dst, src, sizeof(dst)), dst);

// 	strncpy(src, "abc" , sizeof(src));
// 	strncpy(dst, "XX" , sizeof(dst));
// 	printf("dst: '%s', src: '%s'\n", dst, src);
// 	printf("strlcat   : %ld, %s\n", strlcat(dst, src, sizeof(dst)), dst);
// 	strncpy(dst, "XX" , sizeof(dst));
// 	printf("ft_strlcat: %ld, %s\n\n", ft_strlcat(dst, src, sizeof(dst)), dst);

// 	strncpy(src, "" , sizeof(src));
// 	strncpy(dst, "test" , sizeof(dst));
// 	printf("dst: '%s', src: '%s'\n", dst, src);
// 	printf("strlcat   : %ld, %s\n", strlcat(dst, src, sizeof(dst)), dst);
// 	strncpy(dst, "test" , sizeof(dst));
// 	printf("ft_strlcat: %ld, %s\n\n", ft_strlcat(dst, src, sizeof(dst)), dst);

// 	strncpy(src, "t" , sizeof(src));
// 	strncpy(dst, "" , sizeof(dst));
// 	printf("dst: '%s', src: '%s'\n", dst, src);
// 	printf("strlcat   : %ld, %s\n", strlcat(dst, src, sizeof(dst)), dst);
// 	strncpy(dst, "" , sizeof(dst));
// 	printf("ft_strlcat: %ld, %s\n\n", ft_strlcat(dst, src, sizeof(dst)), dst);

// 	strncpy(src, "" , sizeof(src));
// 	strncpy(dst, "" , sizeof(dst));
// 	printf("dst: '%s', src: '%s'\n", dst, src);
// 	printf("strlcat   : %ld, %s\n", strlcat(dst, src, sizeof(dst)), dst);
// 	strncpy(dst, "" , sizeof(dst));
// 	printf("ft_strlcat: %ld, %s\n\n", ft_strlcat(dst, src, sizeof(dst)), dst);
// }
