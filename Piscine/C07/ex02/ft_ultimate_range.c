/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:17:42 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/13 14:40:32 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	irange;
	int	index;
	int	*arr;

	index = 0;
	irange = max - min;
	if (irange <= 0)
	{
		*range = NULL;
		return (0);
	}
	arr = (int *)malloc(irange * sizeof(int));
	if (arr == NULL)
		return (-1);
	while (index < irange)
	{
		arr[index] = min + index;
		index++;
	}
	*range = arr;
	return (irange);
}
