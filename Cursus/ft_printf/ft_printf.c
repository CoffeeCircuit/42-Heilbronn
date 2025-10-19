/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:50:07 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/19 11:38:30 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;

	len = 0;
	va_start(args, format);
	while (format[len])
	{
		if (format[len] == '%')
		{
			
		}
		else
			ft_putchar_fd(format[len], STDOUT_FILENO);
		len++;
	}
	va_end(args);
	return (len);
}
