/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_negative.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:16:31 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/10 11:27:52 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_putchar(int c);

void	ft_is_negative(int n)
{
	char	neg;
	char	pos;

	neg = 'N';
	pos = 'P';
	if (n < 0)
		ft_putchar(neg);
	else
		ft_putchar(pos);
}
