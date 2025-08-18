/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:42:31 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/08 09:44:46 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	src_index;
	unsigned int	dest_index;

	src_index = 0;
	dest_index = 0;
	while (dest[dest_index])
		dest_index++;
	while (src[src_index])
	{
		dest[dest_index] = src[src_index];
		src_index++;
		dest_index++;
	}
	dest[dest_index] = '\0';
	return (dest);
}

// // TEST
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	dest[10];
// 	char	src[] = "test";

// 	ft_strcat(dest, src);
// 	printf("%s\n", dest);
// }
