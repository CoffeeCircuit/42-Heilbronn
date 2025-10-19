/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/18 15:45:45 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <limits.h>

void	ft_test_digits(void)
{
	ft_printf("=== %%d and %%i (signed int) ===\n");
	ft_printf("Default: %d", 42);
	ft_printf("Negative: %d", -42);
	ft_printf("Zero: %d", 0);
	ft_printf("With +: %+d", 42);
	ft_printf("With space: % d", 42);
	ft_printf("With 0: %05d", 42);
	ft_printf("With -: %-5d", 42);
}
