/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:41:14 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 14:13:20 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_h_digit_to_char(int n, char *string, int position)
{
	int	digit;

	while (position >= 1)
	{
		digit = n / position;
		if (digit < 0)
			digit *= -1;
		*string = 48 + digit;
		string++;
		if (n < 0)
			n = n + (digit * position);
		else
			n = n - (digit * position);
		position /= 10;
	}
	*string = '\0';
}

static int	ft_h_conv_pos_to_len(int position)
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

char	*ft_itoa(int n)
{
	int		neg;
	int		position;
	char	*string;

	position = 1000000000;
	neg = 0;
	if (n < 0)
		neg = 1;
	while (n / (position) == 0 && position > 1)
		position /= 10;
	string = malloc(ft_h_conv_pos_to_len(position) + neg + 1);
	if (string == NULL)
		return (NULL);
	if (neg == 1)
	{
		*string = '-';
		string++;
	}
	ft_h_digit_to_char(n, string, position);
	if (neg == 1)
		string--;
	return (string);
}
