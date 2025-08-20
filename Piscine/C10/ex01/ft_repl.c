/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:15:59 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/20 13:18:03 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cat.h"

int	ft_repl(void)
{
	char	buf[BUF_SIZE];
	int		bytes_read;

	bytes_read = -1;
	while (bytes_read)
	{
		bytes_read = read(1, buf, BUF_SIZE);
		write(1, buf, bytes_read);
	}
	return (0);
}
