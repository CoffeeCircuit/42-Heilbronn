/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 07:35:03 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/19 02:11:32 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_arglst(char **arglst)
{
	while (*arglst)
	{
		free(*arglst);
		arglst++;
	}
	arglst = NULL;
}

int	lstlen(char **arglst)
{
	int	len;

	if (!arglst)
		return (0);
	len = 0;
	while (arglst[len])
		len++;
	return (len);
}

void	realloc_stk(t_stk *stk, size_t old, size_t new)
{
	int	*tmp;

	tmp = (int *)ft_calloc(new, sizeof(int));
	ft_memmove(tmp, stk->vals, old * sizeof(int));
	free(stk->vals);
	stk->vals = tmp;
}

int	parse_args_str(t_stk *stk, size_t *len, const char *argv)
{
	int		i;
	int		nbr;
	size_t	old_len;
	char	**arglst;

	i = 0;
	arglst = ft_split(argv, ' ');
	old_len = stk->len;
	stk->len += lstlen(arglst);
	stk->cap = stk->len;
	if (!stk->vals)
		stk->vals = (int *)ft_calloc(stk->cap, sizeof(int));
	else
		realloc_stk(stk, old_len, stk->len);
	if (!stk->vals)
		return (0);
	while (arglst[i])
	{
		nbr = ft_atoi(arglst[i]);
		if (!is_num(arglst[i]) || contains(stk->vals, nbr, stk->len))
			return (free_arglst(arglst), 0);
		stk->vals[i + old_len] = nbr;
		i++;
	}
	return (free_arglst(arglst), free(arglst), 1);
}
