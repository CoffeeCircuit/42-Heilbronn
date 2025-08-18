/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:38:01 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/10 19:40:47 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

int	main(int argc, char **argv)
{
	int	index;

	index = argc - 1;
	while (index)
	{
		write(1, argv[index], ft_strlen(argv[index]));
		write(1, "\n", 1);
		index--;
	}
	return (0);
}
