/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:22:31 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/20 15:48:50 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cat.h"

int	main(int argc, char **argv)
{
	int	file;
	int	arg_index;

	file = -1;
	arg_index = 0;
	if (argc == 1)
		ft_repl();
	else
	{
		while (arg_index++ < argc - 1)
		{
			file = open(argv[arg_index], O_RDONLY);
			if (errno)
			{
				ft_perror(argv[0], argv[arg_index], errno);
				continue ;
			}
			ft_write(file, argv[0], argv[arg_index]);
		}
	}
	return (0);
}
