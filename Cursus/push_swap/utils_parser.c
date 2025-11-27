/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 07:35:03 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/26 21:45:52 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_arglst(char **arglst)
{
	while (*arglst)
	{
		free(*arglst);
		arglst++;
	}
	arglst = NULL;
}

static int	lstlen(char **arglst)
{
	int	len;

	if (!arglst)
		return (0);
	len = 0;
	while (arglst[len])
		len++;
	return (len);
}

static void	realloc_stk(t_stk *stk, size_t old, size_t new)
{
	int	*tmp;

	tmp = (int *)ft_calloc(new, sizeof(int));
	ft_memmove(tmp, stk->vals, old * sizeof(int));
	free(stk->vals);
	stk->vals = tmp;
}

static int	contains(t_stk *stk, int nbr)
{
	size_t	i;

	i = 0;
	if (!stk->len || !stk->vals)
		return (0);
	while (i < stk->len)
	{
		if (stk->vals[i] == nbr)
			return (1);
		i++;
	}
	return (0);
}

int	parse_args_str(t_stk *stk, const char *argv)
{
	int		i;
	int		j;
	int		nbr;
	char	**arglst;

	j = 0;
	arglst = ft_split(argv, ' ');
	stk->cap += lstlen(arglst);
	if (!stk->vals)
		stk->vals = (int *)ft_calloc(stk->cap, sizeof(int));
	else
		realloc_stk(stk, stk->len, stk->cap);
	if (!stk->vals)
		return (0);
	i = stk->len;
	while (arglst[j])
	{
		nbr = ft_atoi(arglst[j]);
		if (!is_num(arglst[j]) || contains(stk, nbr))
			return (free_arglst(arglst), 0);
		stk->vals[i + j] = nbr;
		stk->len++;
		j++;
	}
	return (free_arglst(arglst), free(arglst), 1);
}
