/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 06:44:38 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 03:04:50 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSE_H
# define ARGPARSE_H
# include <stdio.h>
# include "types.h"

int		parse_arguments(int argc, char **argv, t_sim *sim);
void	print_help(FILE *stream, char *program_name);

#endif // CODEXION_ARGPARSE_H
