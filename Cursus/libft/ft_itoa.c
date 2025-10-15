/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 07:57:30 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/13 11:52:52 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*out;
	long long	num;

	num = (long long)n;
	len = ft_numlen(n);
	out = (char *)malloc(len + 1);
	if (out == NULL)
		return (NULL);
	out[len] = '\0';
	if (num < 0)
	{
		num = -num;
		out[0] = '-';
	}
	if (num == 0)
		out[0] = '0';
	while (num)
	{
		out[--len] = '0' + (num % 10);
		num /= 10;
	}
	return (out);
}
