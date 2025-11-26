/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:25:49 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/25 04:59:10 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max_index(int *a, size_t len)
{
	size_t	i;
	int		max;
	int		idx;

	i = 1;
	idx = 0;
	max = a[0];
	while (i < len)
	{
		if (a[i] > max)
		{
			max = a[i];
			idx = i;
		}
		i++;
	}
	return (idx);
}

int	*sort_(int *arr, int len)
{
	int	i;
	int	tmp;
	int	pivot;
	int	*sarr;

	sarr = (int *)ft_calloc(len, sizeof(int));
	pivot = 1;
	ft_memcpy(sarr, arr, len * sizeof(int));
	while (pivot < len)
	{
		i = pivot;
		while (i > 0 && sarr[i - 1] > sarr[i])
		{
			tmp = sarr[i];
			sarr[i] = sarr[i - 1];
			sarr[i - 1] = tmp;
			i--;
		}
		pivot++;
	}
	return (sarr);
}

int	*val_to_idx(int *arr, int len)
{
	int	i;
	int	j;
	int	*iarr;
	int	*sorted_arr;

	i = 0;
	iarr = (int *)ft_calloc(len, sizeof(int));
	if (!iarr)
		return (NULL);
	sorted_arr = sort_(arr, len);
	while (i < len)
	{
		j = 0;
		while (j < len)
			if (sorted_arr[j++] == *arr)
				break ;
		arr++;
		iarr[i++] = j - 1;
	}
	free(sorted_arr);
	return (iarr);
}

t_limit	*get_chunck_range(int len, int count)
{
	int		i;
	int		size;
	t_limit	*chunks;

	size = len / count;
	chunks = (t_limit *)ft_calloc(count + 1, sizeof(t_limit));
	if (!chunks)
		return (NULL);
	i = 0;
	while (i < count - 1)
	{
		chunks[i].min = i * size;
		chunks[i].max = (i + 1) * size - 1;
		i++;
	}
	chunks[i].min = i * size;
	chunks[i].max = len;
	return (chunks);
}

int	find_next_in_chunk(int *arr, int len, t_limit chunk)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arr[i] >= chunk.min && arr[i] <= chunk.max)
			return (i);
		i++;
	}
	return (-1);
}
