/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 06:31:38 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 15:41:34 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_format(t_format *fmt)
{
	fmt->specifier = '\0';
	fmt->width = 0;
	fmt->is_valid = 0;
	fmt->has_plus = 0;
	fmt->has_minus = 0;
	fmt->has_zero = 0;
	fmt->has_hash = 0;
	fmt->has_space = 0;
}

int	ft_dispatch_format(t_format *fmt, va_list args)
{
	if (!fmt || !fmt->is_valid)
		return (0);
	if (fmt->specifier == 'c')
		return (ft_write_char(fmt, va_arg(args, int)));
	else if (fmt->specifier == 's')
		return (ft_write_string(fmt, va_arg(args, char *)));
	else if (fmt->specifier == 'd' || fmt->specifier == 'i')
		return (ft_write_int(fmt, va_arg(args, int)));
	else if (fmt->specifier == 'u')
		return (ft_write_unsigned(fmt, va_arg(args, unsigned int)));
	else if (fmt->specifier == 'x')
		return (ft_write_hex(fmt, va_arg(args, unsigned int), 0));
	else if (fmt->specifier == 'X')
		return (ft_write_hex(fmt, va_arg(args, unsigned int), 1));
	else if (fmt->specifier == 'p')
		return (ft_write_pointer(fmt, va_arg(args, void *)));
	else if (fmt->specifier == '%')
		return (write(STDOUT_FILENO, "%", 1));
	else
		return (0);
}

int	ft_format_output(char **s, va_list args)
{
	t_format	fmt;
	int			len;

	len = 0;
	ft_init_format(&fmt);
	if (**s == '%')
	{
		(*s)++;
		if (**s == '\0')
			return (write(STDOUT_FILENO, "%", 1));
		ft_parse_flags(s, &fmt);
		ft_parse_width(s, &fmt);
		ft_parse_spec(s, &fmt);
		if (fmt.is_valid)
			len += ft_dispatch_format(&fmt, args);
		else
			return (write(STDOUT_FILENO, "%", 1));
	}
	return (len);
}
