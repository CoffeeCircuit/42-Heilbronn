/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/18 09:53:33 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_test_string(void)
{
	ft_printf("=== %%s (string) ===\n");
	ft_printf("Default: %s|\n", "Hello");
	ft_printf("With -: %-10s|\n", "Hello");
	ft_printf("\n");
}
