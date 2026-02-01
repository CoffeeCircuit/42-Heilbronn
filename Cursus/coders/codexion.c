/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:27:58 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 02:50:34 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (!parse_arguments(argc, argv, &sim))
		return (print_help(stderr, "codexion"), 1);
	if (!init_sim(&sim))
		return (destroy_sim(&sim), 0);
	// logic goses in here...
	join_threads(&sim);
	destroy_sim(&sim);
	return (0);
}
