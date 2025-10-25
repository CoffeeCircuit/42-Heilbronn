/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/21 06:14:21 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include "ft_test.h"

void	ft_test_digits(void)
{
	printf("Integer default            : [%d]\n", 42);
	printf("Integer negative           : [%d]\n", -42);
	printf("Integer with +             : [%+d]\n", 42);
	printf("Integer with + (negative)  : [%+d]\n", -42);
	printf("Integer with space         : [% d]\n", 42);
	printf("Integer with space (neg)   : [% d]\n", -42);
	printf("Integer with 0             : [%010d]\n", 42);
	printf("Integer with 0 (negative)  : [%010d]\n", -42);
	printf("Integer with -             : [%-10d]\n", 42);
	printf("Integer with - (negative)  : [%-10d]\n", -42);
	printf("Integer with + and 0       : [%+010d]\n", 42);
	printf("Integer with + and 0 (neg) : [%+010d]\n", -42);
	printf("Integer with - and +       : [%-+10d]\n", 42);
	printf("Integer with - and + (neg) : [%-+10d]\n", -42);
	printf("Integer %%i default         : [%i]\n", 42);
	printf("Integer %%i negative        : [%i]\n", -42);
}
