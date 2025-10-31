/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/31 04:48:34 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

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
	slen = ft_strlen(str);
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
	int	pd;

	len = 0;
	pd = 0;
	n_len = ft_nbrlen(n, 10);
	if (fmt->width > n_len + (n < 0 || fmt->has_space || fmt->has_plus))
		pd = fmt->width - n_len - (n < 0 || fmt->has_space || fmt->has_plus);
	if (fmt->has_plus && fmt->has_zero)
		len += write(STDOUT_FILENO, "+", 1);
	if (n < 0 && fmt->has_zero)
		len += write(STDOUT_FILENO, "-", 1);
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, pd);
	if (n < 0 && !fmt->has_zero)
		len += write(STDOUT_FILENO, "-", 1);
	else if (fmt->has_plus && !fmt->has_zero)
		len += write(STDOUT_FILENO, "+", 1);
	else if (fmt->has_space)
		len += write(STDOUT_FILENO, " ", 1);
	len += ft_write_base(n, "0123456789", 10);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, pd);
	return (len);
}

int	ft_write_unsigned(t_format *fmt, unsigned int n)
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

int	ft_write_hex(t_format *fmt, unsigned int n, int uppercase)
{
	int			len;
	int			n_len;
	int			padding;
	char const	*hex[2] = {"0123456789abcdef", "0123456789ABCDEF"};
	char const	*hex_prefix[2] = {"0x", "0X"};

	len = 0;
	padding = 0;
	n_len = ft_nbrlen(n, 16);
	if (n == 0)
		return (write(STDOUT_FILENO, "0", 1));
	if (fmt->has_hash)
	{
		len += 2;
		write(STDOUT_FILENO, hex_prefix[uppercase], 2);
	}
	if (fmt->width > n_len + 2 * fmt->has_hash)
		padding = fmt->width - n_len - 2 * fmt->has_hash;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	len += ft_write_base(n, hex[uppercase], 16);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}
