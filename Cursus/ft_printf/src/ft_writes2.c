/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/01 18:06:09 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_write_nil(t_format *fmt, int *n_len, int *pad, int *len)
{
	if (fmt->width > *n_len)
		*pad = fmt->width - *n_len;
	if (!fmt->has_minus)
		*len += ft_write_padding(fmt, *pad);
	*len += write(STDOUT_FILENO, "(nil)", 5);
	if (fmt->has_minus)
		*len += ft_write_padding(fmt, *pad);
}

int	ft_ptrlen(uintptr_t nbr, int base)
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

int	ft_write_pointer(t_format *fmt, void *ptr)
{
	uintptr_t	addr;
	int			len;
	int			n_len;
	int			pad;

	len = 0;
	pad = 0;
	if (!ptr)
	{
		n_len = 5;
		ft_write_nil(fmt, &n_len, &pad, &len);
		return (len);
	}
	addr = (uintptr_t)ptr;
	n_len = ft_ptrlen(addr, 16) + 2;
	if (fmt->width > n_len)
		pad = fmt->width - n_len;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, pad);
	len += write(STDOUT_FILENO, "0x", 2);
	len += ft_write_ubase(addr, "0123456789abcdef", 16);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, pad);
	return (len);
}

int	ft_write_zeros(t_format *fmt, int size)
{
	int	len;

	len = 0;
	while (size--)
	{
		if (fmt->has_dot || fmt->has_zero)
			len += write(STDOUT_FILENO, "0", 1);
	}
	return (len);
}

void	ft_zero_ints(int len, ...)
{
	va_list	args;
	int		*ptr;

	va_start(args, len);
	while (len)
	{
		ptr = va_arg(args, int *);
		*ptr = 0;
		len--;
	}
	va_end(args);
}
