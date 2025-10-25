/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/21 06:11:03 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include "ft_test.h"

void	ft_test_hex(void)
{
	printf("Hex default                : [%x]\n", 255);
	printf("Hex with #                 : [%#x]\n", 255);
	printf("Hex with 0                 : [%010x]\n", 255);
	printf("Hex with -                 : [%-10x]\n", 255);
	printf("Hex with # and 0           : [%#010x]\n", 255);
	printf("Hex negative               : [%x]\n", -255);
}
