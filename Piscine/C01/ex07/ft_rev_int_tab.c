/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:28:07 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/05 15:43:41 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_rev_int_tab(int *tab, int size)
{
	int	temp;
	int	lft;
	int	rgt;

	lft = 0;
	rgt = size - 1;
	while (lft < rgt)
	{
		temp = tab[lft];
		tab[lft] = tab[rgt];
		tab[rgt] = temp;
		lft++;
		rgt--;
	}
}
