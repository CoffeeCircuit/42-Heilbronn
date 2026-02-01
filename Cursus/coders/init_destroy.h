/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 02:53:21 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/01 03:00:13 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_DESTROY_H
# define INIT_DESTROY_H
# include "types.h"

int		init_sim(t_sim *sim);
void	join_threads(t_sim *sim);
void	destroy_sim(t_sim *sim);

#endif
