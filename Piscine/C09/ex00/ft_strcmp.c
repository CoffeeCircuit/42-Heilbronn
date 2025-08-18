/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 07:57:26 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/18 14:00:33 by abalcu           ###   ########.fr       */
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
