/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_untils_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:22:25 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/01 18:34:52 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_print_neg_int(t_format *fmt, int *len, int *pad, int n)
{
	if (*pad < 0)
		*pad = 0;
	if (!fmt->has_minus && !(fmt->has_zero && !fmt->has_dot))
		*len += ft_write_padding(fmt, *pad);
	if (n < 0)
		*len += write(1, "-", 1);
	else if (fmt->has_plus)
		*len += write(1, "+", 1);
	else if (fmt->has_space)
		*len += write(1, " ", 1);
	return (*len);
}
