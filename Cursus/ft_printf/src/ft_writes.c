/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/01 18:40:45 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_write_char(t_format *fmt, int c)
{
	int	len;

	len = 0;
	if (!fmt->has_minus && fmt->width)
		len += ft_write_padding(fmt, fmt->width - 1);
	len += write(STDOUT_FILENO, &c, 1);
	if (fmt->has_minus && fmt->width)
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
	if (!str && (!fmt->has_dot || fmt->precision >= 6))
		str = "(null)";
	if (!str)
		slen = 0;
	else
		slen = ft_strlen(str);
	if (fmt->has_dot && fmt->precision < slen)
		slen = fmt->precision;
	if (fmt->has_dot && fmt->precision == 0)
		slen = 0;
	if (fmt->width > slen)
		padding = fmt->width - slen;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	if (slen > 0)
		len += write(STDOUT_FILENO, str, slen);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}

int	ft_write_int(t_format *fmt, int n)
{
	int	len;
	int	n_len;
	int	sign;
	int	zero;
	int	pad;

	ft_zero_ints(3, &len, &n_len, &zero);
	sign = (n < 0 || fmt->has_plus || fmt->has_space);
	if (!(fmt->has_dot && fmt->precision == 0 && n == 0))
		n_len = ft_nbrlen(n, 10);
	if (fmt->has_dot && fmt->precision > n_len)
		zero = fmt->precision - n_len;
	pad = fmt->width - n_len - zero - sign;
	ft_print_neg_int(fmt, &len, &pad, n);
	if (!fmt->has_minus && fmt->has_zero && !fmt->has_dot)
		len += ft_write_zeros(fmt, pad);
	len += ft_write_zeros(fmt, zero);
	if (!(fmt->has_dot && fmt->precision == 0 && n == 0))
		len += ft_write_base(n, "0123456789", 10);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, pad);
	return (len);
}

int	ft_write_unsigned(t_format *fmt, unsigned int n)
{
	int	len;
	int	n_len;
	int	zero_pad;
	int	padding;

	ft_zero_ints(4, &len, &n_len, &padding, &zero_pad);
	if (!(n == 0 && fmt->has_dot && fmt->precision == 0))
		n_len = ft_nbrlen(n, 10);
	if (fmt->has_dot && fmt->precision > n_len)
		zero_pad = fmt->precision - n_len;
	if (fmt->width > n_len + zero_pad)
		padding = fmt->width - n_len - zero_pad;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	len += ft_write_zeros(fmt, zero_pad);
	if (!(fmt->has_dot && fmt->precision == 0 && n == 0))
		len += ft_write_base(n, "0123456789", 10);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}

int	ft_write_hex(t_format *fmt, unsigned int n, int uppercase)
{
	const char	*hex[] = {"0123456789abcdef", "0123456789ABCDEF", "0x", "0X"};
	int			len;
	int			pad;
	int			zero;
	int			n_len;

	ft_zero_ints(4, &len, &pad, &zero, &n_len);
	if (!(fmt->has_dot && fmt->precision == 0 && n == 0))
		n_len = ft_nbrlen(n, 16);
	if (fmt->has_dot && fmt->precision > n_len)
		zero = fmt->precision - n_len;
	if (fmt->has_hash && n != 0)
		n_len += 2;
	if (fmt->width > n_len + zero)
		pad = fmt->width - n_len - zero;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, pad);
	if (fmt->has_hash && n != 0)
		len += write(STDOUT_FILENO, hex[uppercase + 2], 2);
	len += ft_write_zeros(fmt, zero);
	if (!(fmt->has_dot && fmt->precision == 0 && n == 0))
		len += ft_write_base(n, hex[uppercase], 16);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, pad);
	return (len);
}
