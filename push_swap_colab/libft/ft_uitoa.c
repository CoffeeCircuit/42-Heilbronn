/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:06:54 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/16 21:06:49 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_h_digit_to_char(unsigned int n, char *string, int position)
{
	int	digit;

	while (position >= 1)
	{
		digit = n / position;
		*string = 48 + digit;
		string++;
		n = n - (digit * position);
		position /= 10;
	}
	*string = '\0';
}

static int	ft_h_conv_pos_to_len(long position)
{
	int	len;

	len = 1;
	while (position > 1)
	{
		len++;
		position /= 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	long	position;
	char	*string;

	position = 1000000000;
	while (n / (position) == 0 && position > 1)
		position /= 10;
	string = malloc(ft_h_conv_pos_to_len(position) + 1);
	if (string == NULL)
		return (NULL);
	ft_h_digit_to_char(n, string, position);
	return (string);
}
