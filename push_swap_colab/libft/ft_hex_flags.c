/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:08:40 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/07 15:29:02 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_h_janitor(char *table, char *hex_num)
{
	free(hex_num);
	free(table);
	return (NULL);
}

char	*ft_h_conv_i_dec_to_c_hex(size_t num)
{
	size_t	num_cpy;
	int		len;
	char	*table;
	char	*hex_num;

	table = ft_strdup("0123456789abcdef");
	num_cpy = num;
	len = 1;
	while (num_cpy >= 16)
	{
		len++;
		num_cpy /= 16;
	}
	hex_num = ft_calloc(len + 1, 1);
	if (table == NULL || hex_num == NULL)
		return (ft_h_janitor(table, hex_num));
	hex_num[len] = '\0';
	while (--len >= 0)
	{
		hex_num[len] = table[num % 16];
		num /= 16;
	}
	free(table);
	return (hex_num);
}

size_t	ft_h_flag_x(va_list args)
{
	unsigned int	num;
	char			*hex_num;
	size_t			len;

	num = va_arg(args, size_t);
	hex_num = ft_h_conv_i_dec_to_c_hex(num);
	if (hex_num == NULL)
		return (0);
	ft_putstr_fd(hex_num, 1);
	len = ft_strlen(hex_num);
	free(hex_num);
	return (len);
}

size_t	ft_h_flag_up_x(va_list args)
{
	size_t	num;
	char	*hex_num;
	size_t	len;
	int		iterator;

	num = va_arg(args, unsigned int);
	hex_num = ft_h_conv_i_dec_to_c_hex(num);
	if (hex_num == NULL)
		return (0);
	iterator = 0;
	while (hex_num[iterator] != '\0')
	{
		hex_num[iterator] = ft_toupper(hex_num[iterator]);
		iterator++;
	}
	ft_putstr_fd(hex_num, 1);
	len = ft_strlen(hex_num);
	free(hex_num);
	return (len);
}

size_t	ft_h_flag_p(va_list args)
{
	size_t	ptr;
	char	*hex_num;
	size_t	len;

	ptr = va_arg(args, size_t);
	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	hex_num = ft_h_conv_i_dec_to_c_hex(ptr);
	if (hex_num == NULL)
		return (0);
	ft_putchar_fd('0', 1);
	ft_putchar_fd('x', 1);
	ft_putstr_fd(hex_num, 1);
	len = ft_strlen(hex_num);
	free(hex_num);
	return (len + 2);
}
