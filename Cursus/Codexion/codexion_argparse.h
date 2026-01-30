/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_argparse.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 06:44:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/01/30 06:54:59 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_ARGPARSE_H
# define CODEXION_ARGPARSE_H
# include <stdio.h>
# include "codexion_types.h"

int		parse_arguments(int argc, char **argv, t_sim *sim);
void	print_help(FILE *stream, char *program_name);


#endif // CODEXION_ARGPARSE_H

