/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:44:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/07 13:47:55 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_symbol(char chr)
{
	if (chr >= 32 && chr <= 47)
		return (1);
	else if (chr >= 58 && chr <= 64)
		return (1);
	else if (chr >= 91 && chr <= 96)
		return (1);
	else if (chr >= 123 && chr <= 126)
		return (1);
	else
		return (0);
}

char	*ft_strcapitalize(char *str)
{
	unsigned int	index;
	unsigned char	is_alpha;
	unsigned char	lowercase_alpha;
	unsigned char	uppercase_alpha;

	index = 0;
	while (str[index])
	{
		lowercase_alpha = (str[index] | 0x20);
		uppercase_alpha = lowercase_alpha ^ (1 << 5);
		is_alpha = lowercase_alpha - 'a';
		if (is_alpha <= 25)
		{
			if (index == 0 || ft_is_symbol(str[index - 1]))
				str[index] = uppercase_alpha;
			else
				str[index] = lowercase_alpha;
		}
		index++;
	}
	return (str);
}
