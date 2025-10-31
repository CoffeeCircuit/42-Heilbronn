/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:13 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/31 04:10:55 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_pointer(t_format *fmt, void *ptr)
{
	int	len;
	int	n_len;
	int	padding;

	len = 2;
	padding = 0;
	n_len = ft_nbrlen((size_t)ptr, 16);
	if (!ptr)
		return (write(STDOUT_FILENO, "(nil)", 5));
	if (fmt->width > n_len + 2)
		padding = fmt->width - n_len - 2;
	if (!fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	write(STDOUT_FILENO, "0x", 2);
	len += ft_write_base((size_t)ptr, "0123456789abcdef", 16);
	if (fmt->has_minus)
		len += ft_write_padding(fmt, padding);
	return (len);
}
