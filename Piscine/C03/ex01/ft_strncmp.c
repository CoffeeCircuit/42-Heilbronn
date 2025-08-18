/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:42:16 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/09 12:53:28 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	index;
	unsigned char	s1_char;
	unsigned char	s2_char;

	index = 0;
	while ((s1[index] || s2[index]) && index < n)
	{
		s1_char = s1[index];
		s2_char = s2[index];
		if (s1_char - s2_char != 0)
			return (s1_char - s2_char);
		index++;
	}
	return (0);
}

// // TESTS
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *s1, *s2;
// 	unsigned int n;

// 	s1 = "ABC"; 	s2 = "ABD"; 	n = 2;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// 	s1 = "ABC"; 	s2 = "ABD"; 	n = 3;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// 	s1 = "ABD"; 	s2 = "ABC"; 	n = 3;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// 	s1 = "A"; 	s2 = "C"; 	n = 0;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// 	s1 = "A"; 	s2 = "AC"; 	n = 2;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// 	s1 = ""; 	s2 = "AC"; 	n = 2;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// 	s1 = "\201"; 	s2 = "A"; 	n = 2;
// 	printf("ft_strncmp:(%s, %s, %d) = %d\n", s1, s2, n, ft_strncmp(s1, s2, n));
// 	printf("strncmp   :(%s, %s, %d) = %d\n", s1, s2, n, strncmp(s1, s2, n));
// 	printf("----------------------------------------\n");
// }
