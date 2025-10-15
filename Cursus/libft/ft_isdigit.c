/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:59:11 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/14 08:32:26 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	if (chr >= '0' && chr <= '9')
		return (IS_DIGIT);
	return (0);
}
