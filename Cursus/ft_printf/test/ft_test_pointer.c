/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/18 09:53:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_test_pointer(void)
{
	int	x;
	int	*ptr;

	x = 42;
	ptr = &x;
	ft_printf("=== %%p (pointer) ===\n");
	ft_printf("Pointer: %p|\n", ptr);
	ft_printf("NULL pointer: %p|\n", (void *)0);
}
