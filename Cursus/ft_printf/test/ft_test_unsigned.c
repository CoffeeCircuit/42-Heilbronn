/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/21 06:11:09 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include "ft_test.h"

void	ft_test_unsigned(void)
{
	printf("Unsigned default           : [%u]\n", 42);
	printf("Unsigned With 0            : [%05u]\n", 42u);
	printf("Unsigned With -            : [%-5u]\n", 42u);
	printf("Unsigned large             : [%u]\n", 4294967295U);
}
