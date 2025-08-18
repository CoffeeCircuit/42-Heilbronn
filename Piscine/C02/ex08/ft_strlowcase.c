/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:34:24 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 13:46:19 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strlowcase(char *str)
{
	unsigned int	index;
	unsigned char	uppercase_alpha;

	index = 0;
	while (str[index])
	{
		uppercase_alpha = str[index] - 'A';
		if (uppercase_alpha <= 25)
			str[index] |= 0x20;
		index++;
	}
	return (str);
}
