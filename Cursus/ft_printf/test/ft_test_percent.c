/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:03:15 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/18 09:53:25 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_test_percent(void)
{
	ft_printf("=== Literal %% ===\n");
	ft_printf("Just a percent: %%|\n");
	ft_printf("Formatted: %-5%%|\n");
}
