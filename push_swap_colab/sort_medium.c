/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 04:15:44 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/17 06:55:20 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef struct s_limit
{
	int	min;
	int	max;
}		t_limit;

int	max_index(int *a, size_t len)
{
	int	i;
	int	max;
	int	idx;

	i = 0;
	max = a[0];
	idx = 0;
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

// value to index
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

t_limit	*get_chunck_range(int size, int count)
{
	int		i;
	t_limit	*chunks;

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
	chunks[i].max = (i + 1) * size;
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

// Chunk sorting
void	medium_sort(t_stk *a, t_stk *b)
{
	int		pos;
	int		cnk_c;
	t_limit	*cnks;
	int		i;
	int		max_i;
	int		mid;
	int		*tmp;

	cnk_c = 5;
	tmp = val_to_idx(a->vals, a->len);
	free(a->vals);
	a->vals = tmp;
	cnks = get_chunck_range(a->len / cnk_c, cnk_c);
	i = 0;
	while (i < cnk_c)
	{
		while (1)
		{
			pos = find_next_in_chunk(a->vals, a->len, cnks[i]);
			if (pos == -1)
				break ;
			if (pos < a->len / 2)
				while (pos--)
					r(a);
			else
			{
				pos = a->len - pos;
				while (pos--)
					rr(a);
			}
			mid = (cnks[i].min + cnks[i].max) / 2;
			if (a->vals[0] < mid)
			{
				p(b, a);
				r(b);
			}
			else
				p(b, a);
		}
		i++;
	}
	while (b->len)
	{
		max_i = max_index(b->vals, b->len);
		if (max_i < b->len / 2)
			while (max_i--)
				r(b);
		else
		{
			max_i = b->len - max_i;
			while (max_i--)
				rr(b);
		}
		p(a, b);
	}
	free(cnks);
}


//TODO
// check logic, sometimes it works other times it doesn't
// check parser since when 0 is give then if prints Error
// Downloads ARG="3 2"; ./push_swap --medium $ARG | ./checker_linux $ARG
// OK
// ➜  Downloads ARG="3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// KO
// ➜  Downloads ARG="4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// KO
// ➜  Downloads ARG="5 4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// OK
// ➜  Downloads ARG="6 5 4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// OK
// ➜  Downloads ARG="7 6 5 4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// OK
// ➜  Downloads ARG="8 7 6 5 4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// KO
// ➜  Downloads ARG="9 8 7 6 5 4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// KO
// ➜  Downloads ARG="10 9 8 7 6 5 4 3 2 1"; ./push_swap --medium $ARG | ./checker_linux $ARG
// OK
// ➜  Downloads ARG="10 9 8 7 6 5 4 3 2 1 0"; ./push_swap --medium $ARG | ./checker_linux $ARG
// Error
// KO

