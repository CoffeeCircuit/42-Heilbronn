/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:18:05 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 13:45:28 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strupcase(char *str)
{
	unsigned int	index;
	unsigned char	lowercase_alpha;

	index = 0;
	while (str[index])
	{
		lowercase_alpha = str[index] - 'a';
		if (lowercase_alpha <= 25)
			str[index] ^= (1 << 5);
		index++;
	}
	return (str);
}
