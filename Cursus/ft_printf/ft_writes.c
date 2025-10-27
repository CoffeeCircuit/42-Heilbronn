/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 17:23:50 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_char(t_format *fmt, int c)
{
	int	len;

	len = 0;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, fmt->width - 1);
	len += write(STDOUT_FILENO, &c, 1);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, fmt->width - 1);
	return (len);
}

int	ft_write_string(t_format *fmt, char *str)
{
	int	len;
	int	slen;
	int	padding;

	len = 0;
	padding = 0;
	if (!str)
		str = "(null)";
	slen = strlen(str);
	if (fmt->width > slen)
		padding = fmt->width - slen;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	len += write(STDOUT_FILENO, str, slen);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}

int	ft_write_int(t_format *fmt, int n)
{
	int	len;
	int	n_len;
	int	padding;

	len = 0;
	padding = 0;
	n_len = ft_nbrlen(n, 10);
	if (fmt->width > n_len)
		padding = fmt->width - n_len;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	len += ft_write_base(n, "0123456789", 10);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}

int	ft_write_unsigned(t_format *fmt, unsigned int n);
