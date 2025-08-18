/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:37:44 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 13:33:55 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_numeric(char *str)
{
	unsigned int	index;
	unsigned char	digit;

	index = 0;
	while (str[index])
	{
		digit = str[index] - '0';
		if (digit > 9)
			return (0);
		index++;
	}
	return (1);
}
