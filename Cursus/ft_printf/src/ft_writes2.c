/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/31 17:25:51 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_write_pointer(t_format *fmt, void *ptr)
{
	int			len;
	int			n_len;
	int			padding;
	uintptr_t	addr;

	if (!ptr)
		return (write(STDOUT_FILENO, "(nil)", 5));
	addr = (uintptr_t)ptr;
	n_len = ft_nbrlen(addr, 16);
	padding = 0;
	if (fmt->width > n_len + 2)
		padding = fmt->width - n_len - 2;
	len = 2;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	write(STDOUT_FILENO, "0x", 2);
	len += ft_write_ubase(addr, "0123456789abcdef", 16);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}

int	ft_write_zeros(t_format *fmt, int size)
{
	int	len;

	len = 0;
	while (size--)
	{
		if (fmt->has_dot)
			len += write(STDOUT_FILENO, "0", 1);
	}
	return (len);
}
