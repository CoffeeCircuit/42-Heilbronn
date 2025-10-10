/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:33:55 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/10 11:48:57 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	*arr;

	if (min >= max)
		return (NULL);
	i = 0;
	arr = (int *)malloc(sizeof(int) * (max - min));
	if (arr == NULL)
		return (NULL);
	while (i < (max - min))
	{
		arr[i] = min + i;
		i++;
	}
	return (arr);
}
