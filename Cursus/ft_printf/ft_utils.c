/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:35:33 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 17:23:59 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbrlen(size_t nbr, int base)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		len++;
		nbr /= base;
	}
	return (len);
}

int	ft_write_rec_nbr(unsigned long n, const char *base_chars, int base)
{
	int	len;

	len = 0;
	if (n >= (unsigned long)base)
		len += ft_write_rec_nbr(n / base, base_chars, base);
	len += write(STDOUT_FILENO, &base_chars[n % base], 1);
	return (len);
}

int	ft_write_base(long n, const char *base_chars, int base)
{
	int				len;
	unsigned long	us_n;

	len = 0;
	if (n < 0 && base == 10)
	{
		len += write(STDOUT_FILENO, "-", 1);
		us_n = (unsigned long)(-n);
	}
	else
		us_n = (unsigned long)n;
	len += ft_write_rec_nbr(us_n, base_chars, base);
	return (len);
}

int	ft_write_padding(t_format *fmt, int size)
{
	int	len;

	len = 0;
	while (size--)
	{
		if (fmt->has_zero)
			len += write(STDOUT_FILENO, "0", 1);
		else
			len += write(STDOUT_FILENO, " ", 1);
	}
	return (len);
}
