/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:00:21 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/14 11:20:54 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	range;
	int	*arr;
	int	index;

	index = 0;
	arr = NULL;
	if (min >= max)
		return (NULL);
	range = max - min;
	arr = (int *)malloc(range * sizeof(int));
	if (arr == NULL)
		return (NULL);
	while (index < range)
	{
		arr[index] = min + index;
		index++;
	}
	return (arr);
}
