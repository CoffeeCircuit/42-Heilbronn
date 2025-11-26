/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ops1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:00:27 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/24 23:00:30 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(int *arr)
{
	arr[0] ^= arr[1];
	arr[1] ^= arr[0];
	arr[0] ^= arr[1];
}

void	rotate(int *arr, size_t len)
{
	int	tmp;

	tmp = arr[0];
	ft_memmove(arr, &arr[1], (len - 1) * sizeof(int));
	arr[len - 1] = tmp;
}

void	rrotate(int *arr, size_t len)
{
	int	tmp;

	tmp = arr[len - 1];
	ft_memmove(&arr[1], arr, (len - 1) * sizeof(int));
	arr[0] = tmp;
}

int	pop(int *arr, size_t *len)
{
	int	tmp;

	tmp = arr[0];
	ft_memmove(arr, &arr[1], (*len - 1) * sizeof(int));
	(*len)--;
	return (tmp);
}

void	push(int val, int *arr, size_t *len)
{
	if (*len)
		ft_memmove(&arr[1], arr, (*len) * sizeof(int));
	arr[0] = val;
	(*len)++;
}
