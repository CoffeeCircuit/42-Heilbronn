/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:43:14 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/09 13:00:10 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlen(char *str)
{
	unsigned int	index;
	unsigned int	len;

	index = 0;
	len = 0;
	while (str[index])
	{
		len++;
		index++;
	}
	return (len);
}

int	ft_char_pos(char *str, char *chr)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == *chr)
			return (index);
		index++;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	char			*substr;
	int				pos;
	unsigned int	index;
	unsigned int	to_find_len;

	substr = (void *)0;
	to_find_len = ft_strlen(to_find);
	pos = ft_char_pos(str, to_find);
	index = 0;
	if (pos != -1)
	{
		while (str[pos + index] == to_find[index] && to_find_len)
		{
			index++;
			to_find_len--;
		}
	}
	if (to_find_len == 0)
	{
		substr = &str[pos];
		return (substr);
	}
	else
		return (substr);
}

// #include <assert.h>
// #include <stdio.h>#include <assert.h>
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*test;
// 	char	*test2;
// 	char	*test3;

// 	test = "this is a test";
// 	printf("Check    : ft_strstr('%s', '%s')\n", test, "is");
// 	printf("strstr   : %p\nft_strstr: %p\n\n", strstr(test, "is"),
// 		ft_strstr(test, "is"));
// 	assert(strstr(test, "is") == ft_strstr(test, "is"));
// 	printf("Check    : ft_strstr('%s, '%s')\n", test, "");
// 	printf("strstr   : %p\nft_strstr: %p\n\n", strstr(test, ""), ft_strstr(test,
// 			""));
// 	assert(strstr(test, "") == ft_strstr(test, ""));
// 	test2 = "an";
// 	printf("Check    : ft_strstr('%s', '%s')\n", test2, "another");
// 	printf("strstr   : %p\nft_strstr: %p\n\n", strstr(test2, "another"),
// 		ft_strstr(test2, "another"));
// 	assert(strstr(test2, "another") == ft_strstr(test2, "another"));
// 	printf("Check    : ft_strstr('%s', '%s')\n", test2, "a");
// 	printf("strstr   : %p\nft_strstr: %p\n\n", strstr(test2, "a"),
// 		ft_strstr(test2, "a"));
// 	assert(strstr(test2, "a") == ft_strstr(test2, "a"));
// 	test3 = "";
// 	printf("Check    : ft_strstr('%s', '%s')\n", test3, "something");
// 	printf("strstr   : %p\nft_strstr: %p\n\n", strstr(test3, "something"),
// 		ft_strstr(test3, "something"));
// 	assert(strstr(test3, "something") == ft_strstr(test3, "something"));
// 	printf("Check    : ft_strstr('%s', '%s')\n", test3, "");
// 	printf("strstr   : %p\nft_strstr: %p\n\n", strstr(test3, ""),
// 		ft_strstr(test3, ""));
// 	assert(strstr(test3, "") == ft_strstr(test3, ""));
// }
