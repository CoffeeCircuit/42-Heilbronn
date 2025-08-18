/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:04:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 13:30:46 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *str)
{
	unsigned int	index;
	unsigned char	lowercase_alpha;

	index = 0;
	while (str[index])
	{
		lowercase_alpha = (str[index] | 0x20) - 'a';
		if (lowercase_alpha > 25)
			return (0);
		index++;
	}
	return (1);
}
