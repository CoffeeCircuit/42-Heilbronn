/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/18 09:53:39 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <limits.h>

void	ft_test_unsigned(void)
{
	ft_printf("=== %%u (unsigned int) ===\n");
	ft_printf("Default: %u|\n", 42u);
	ft_printf("Zero: %u|\n", 0u);
	ft_printf("INT_MAX: %u|\n", (unsigned int)INT_MAX);
	ft_printf("With 0: %05u|\n", 42u);
	ft_printf("With -: %-5u|\n", 42u);
}
