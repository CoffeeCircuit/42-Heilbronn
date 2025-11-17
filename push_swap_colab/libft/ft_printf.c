/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 01:30:47 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/07 15:29:40 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_h_flag_percent(void);
size_t	ft_h_flag_c(va_list args);
size_t	ft_h_flag_s(va_list args);
size_t	ft_h_flag_p(va_list args);
size_t	ft_h_flag_d_i(va_list args);
size_t	ft_h_flag_u(va_list args);
size_t	ft_h_flag_x(va_list args);
size_t	ft_h_flag_up_x(va_list args);

size_t	ft_h_flag_none(const char *s)
{
	ft_putchar_fd('%', 1);
	if (*s != '\0')
	{
		ft_putchar_fd(*s, 1);
		return (2);
	}
	return (1);
}

size_t	ft_h_handle_format(const char *s, va_list args)
{
	if (*s == 'c')
		return (ft_h_flag_c(args));
	else if (*s == 's')
		return (ft_h_flag_s(args));
	else if (*s == 'p')
		return (ft_h_flag_p(args));
	else if (*s == 'd' || *s == 'i')
		return (ft_h_flag_d_i(args));
	else if (*s == 'u')
		return (ft_h_flag_u(args));
	else if (*s == 'x')
		return (ft_h_flag_x(args));
	else if (*s == 'X')
		return (ft_h_flag_up_x(args));
	else if (*s == '%')
		return (ft_h_flag_percent());
	else
		return (ft_h_flag_none(s));
}

int	ft_h_prnt_str(const char *s, va_list args)
{
	size_t	char_count;
	size_t	conv_char_count;

	char_count = 0;
	while (*s != '\0')
	{
		if (*s == '%')
		{
			s++;
			conv_char_count = ft_h_handle_format(s, args);
			if (conv_char_count == 0 && *s != 's')
				return (-1);
			char_count += conv_char_count;
			if (*s != '\0')
				s++;
		}
		else
		{
			ft_putchar_fd(*s, 1);
			s++;
			char_count++;
		}
	}
	return (char_count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		char_count;

	va_start (args, s);
	char_count = ft_h_prnt_str(s, args);
	va_end(args);
	return (char_count);
}
