/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:42:52 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/08 09:47:20 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	src_index;
	unsigned int	dest_index;

	src_index = 0;
	dest_index = 0;
	while (dest[dest_index])
		dest_index++;
	while (src[src_index] && src_index < nb)
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
// 	strcpy(dest, "XX");
// 	char	src[] = "test";

// 	ft_strncat(dest, src, 2);
// 	printf("%s\n", dest);
// }
