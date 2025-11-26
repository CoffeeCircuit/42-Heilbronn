/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:01:20 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/24 23:21:05 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parse_numargs(t_stk *stk, int *pos, int argc, char const *argv[])
{
	while (*pos < argc)
	{
		if (!parse_args_str(stk, argv[*pos]))
			return (free(stk->vals), ft_perror(), 0);
		(*pos)++;
	}
	if (!stk->len)
		return (free(stk->vals), ft_perror(), 0);
	return (1);
}
