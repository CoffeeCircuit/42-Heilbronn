/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:51:35 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 13:37:54 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	unsigned int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] > 'z' || str[index] < 'a')
			return (0);
		index++;
	}
	return (1);
}
