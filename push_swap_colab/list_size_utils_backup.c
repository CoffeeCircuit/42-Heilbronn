/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size_utils_backup.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:57:11 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/17 21:17:49 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	get_first_list_size_a(t_stk *stk)
{
	size_t	size;

	size = 0;
	size = 0;
	if (stk->len == 0)
		return (0);
	while (size < stk->len - 1)
	{
		if (stk->vals[size] > stk->vals[size + 1])
			break ;
		size++;
	}
	return (size + 1);
}

size_t	get_last_list_size_a(t_stk *stk, size_t l1l)
{
	size_t	size;

	size = 0;
	size = 0;
	if (stk->len - l1l == 0)
		return (0);
	while (size < stk->len - l1l - 1)
	{
		if (stk->vals[size + l1l] > stk->vals[size + l1l + 1])
			break ;
		size++;
	}
	return (size + 1);
}

size_t	get_first_list_size_b(t_stk *stk)
{
	size_t	size;

	size = 0;
	size = 0;
	if (stk->len == 0)
		return (0);
	while (size < stk->len - 1)
	{
		if (stk->vals[size] < stk->vals[size + 1])
			break ;
		size++;
	}
	return (size + 1);
}

size_t	get_last_list_size_b(t_stk *stk, size_t l1l)
{
	size_t	size;

	size = 0;
	if (stk->len - l1l == 0)
		return (0);
	while (size < stk->len - l1l - 1)
	{
		if (stk->vals[size + l1l] < stk->vals[size + l1l + 1])
			break ;
		size++;
	}
	return (size + 1);
}
