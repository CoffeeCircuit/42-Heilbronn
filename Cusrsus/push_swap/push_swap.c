/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:01:08 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/24 23:20:56 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char const *argv[])
{
	int		pos;
	t_stk	a;
	t_stk	b;

	if (argc < 2)
		return (1);
	pos = 1;
	a = (t_stk){.name = 'a', .len = 0, .vals = 0};
	b = (t_stk){.name = 'b', .len = 0, .vals = 0};
	if (!parse_numargs(&a, &pos, argc, argv))
		return (1);
	b.vals = (int *)ft_calloc(a.cap, sizeof(int));
	if (!b.vals)
		return (free(a.vals), ft_perror(), 1);
	b.cap = a.cap;
	ps_sort(&a, &b);
	return (free(a.vals), free(b.vals), 0);
}
