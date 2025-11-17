/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:15:44 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/17 02:40:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef struct s_limit
{
	int	min;
	int	max;
}		t_limit;

int	max_val(int *a, size_t len)
{
	int	i;
	int	max;

	i = 1;
	max = a[0];
	while (i < len)
	{
		if (max > a[i])
			max = a[i];
		i++;
	}
	return (max);
}

int	count_digits(int nbr)
{
	int	count;

	count = 0;
	while (nbr)
	{
		count++;
		nbr /= 10;
	}
	return (count);
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

// value to index
int	*vtoi_arr(int *arr, int len)
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
		iarr[i++] = j-1;
	}
	free(sorted_arr);
	return (iarr);
}


int	main(void)
{
	int	arr[] = {49,48,47,46,45,44,43,42,41,40};
	int	*iarr;

	iarr = vtoi_arr(arr, sizeof(arr)/sizeof(int));
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
		ft_putnbr_fd(iarr[i], 1);
}

// Bucket sort
void	medium_sort(t_stk *a, t_stk *b)
{
	int	*s_a;
	int	chunck_size;
	int	chunck_count;

	s_a = sort_(a->vals, a->len);
	chunck_size = a->len / 5;
}
