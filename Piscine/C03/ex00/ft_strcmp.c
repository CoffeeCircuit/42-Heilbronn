/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:41:49 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/09 12:53:11 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int				index;
	unsigned char	s1_char;
	unsigned char	s2_char;

	index = 0;
	while (s1[index] || s2[index])
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
// 	s1 = "ABC";
// 	s2 = "ABC";
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "ABC";
// 	s2 = "AB";
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "A";
// 	s2 = "AB";
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "ABA";
// 	s2 = "ABZ";
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "ABJ";
// 	s2 = "ABC";
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "\x81";
// 	s2 = "A";
// 	ft_strcmp(s1, s2);
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "abc";
// 	s2 = "aBc";
// 	ft_strcmp(s1, s2);
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// 	s1 = "";
// 	s2 = "";
// 	ft_strcmp(s1, s2);
// 	printf("ft_strcmp:(%s, %s) = %d\n", s1, s2, ft_strcmp(s1, s2));
// 	printf("strcmp   :(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
// 	printf("----------------------------------------\n");
// }
