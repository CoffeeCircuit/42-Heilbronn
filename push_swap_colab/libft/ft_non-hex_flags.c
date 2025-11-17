/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_non-hex_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:12:42 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/07 15:29:12 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_h_flag_c(va_list args)
{
	char	c;
	int		c_val;

	c_val = va_arg(args, int);
	c = (char)c_val;
	ft_putchar_fd(c, 1);
	return (1);
}

size_t	ft_h_flag_s(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

size_t	ft_h_flag_d_i(va_list args)
{
	char	*str;
	size_t	len;
	int		num;

	num = va_arg(args, int);
	str = ft_itoa(num);
	if (str == NULL)
		return (0);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

size_t	ft_h_flag_u(va_list args)
{
	char	*str;
	size_t	len;

	str = ft_uitoa(va_arg(args, unsigned int));
	if (str == NULL)
		return (0);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

size_t	ft_h_flag_percent(void)
{
	ft_putchar_fd('%', 1);
	return (1);
}
