/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:08:22 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/10 10:57:32 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_putchar(int c);

int	main(int argc, char *argv[])
{
	char	*carg;
	int		i;

	i = 1;
	while (i < argc)
	{
		carg = argv[i++];
		while (*carg)
			ft_putchar(*carg++);
		ft_putchar('\n');
	}
	return (0);
}
