/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/18 09:53:22 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_test_hex(void)
{
	ft_printf("=== %%x and %%X (hex) ===\n");
	ft_printf("Default %%x: %x|\n", 255);
	ft_printf("Default %%X: %X|\n", 255);
	ft_printf("Zero %%x: %x|\n", 0);
	ft_printf("With #: %#x|\n", 255);
	ft_printf("With #: %#X|\n", 255);
	ft_printf("With 0: %05x|\n", 255);
	ft_printf("With -: %-5x|\n", 255);
	ft_printf("With -#: %-#5x|\n", 255);
	ft_printf("With -#: %-#5X|\n", 255);
}
