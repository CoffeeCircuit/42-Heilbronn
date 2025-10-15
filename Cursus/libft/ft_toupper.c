/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:09:26 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/13 11:55:40 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	if (ft_isalpha(c))
	{
		chr &= ~0x20;
		return (chr);
	}
	else
		return (c);
}
