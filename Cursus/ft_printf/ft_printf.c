/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:50:07 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 18:38:05 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		len;
	char	*iformat;
	va_list	args;

	len = 0;
	iformat = (char *)format;
	va_start(args, format);
	while (*iformat)
	{
		if (*iformat != '%')
			len += write(STDOUT_FILENO, &(*iformat++), 1);
		else
			len += ft_format_output(&iformat, args);
	}
	va_end(args);
	return (len);
}
