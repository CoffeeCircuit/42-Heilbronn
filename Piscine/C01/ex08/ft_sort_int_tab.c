/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:36:01 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/05 13:08:12 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, int size)
{
	int	pivot;
	int	temp;
	int	index;

	pivot = 1;
	while (pivot < size)
	{
		index = pivot;
		while (index > 0 && tab[index - 1] > tab[index])
		{
			temp = tab[index];
			tab[index] = tab[index - 1];
			tab[index - 1] = temp;
			index--;
		}
		pivot++;
	}
}
