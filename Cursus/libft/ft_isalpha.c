/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 08:52:45 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/15 05:48:43 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	if ((chr >= 'A' && chr <= 'Z') || (chr >= 'a' && chr <= 'z'))
		return (IS_ALPHA);
	return (0);
}
