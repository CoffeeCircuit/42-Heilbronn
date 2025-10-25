/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:50:07 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/21 06:30:49 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int			len;
	va_list		args;
	t_format	*fmt;
	char		*str;

	len = 0;
	str = (char *)format;
	va_start(args, format);
	while (str[len])
	{
		if (str[len] == '%')
		{
			fmt = ft_parse(&str[++len]);
			ft_putarg(fmt, args);
			len += fmt->position - &str[len];
			free(fmt);
		}
		else
			ft_putchar_fd(str[len++], STDOUT_FILENO);
	}
	va_end(args);
	return (len);
}

int	main(void)
{
	size_t	test;

	test = -255;
}
