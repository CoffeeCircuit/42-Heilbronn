/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_coder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 04:11:21 by abalcu            #+#    #+#             */
/*   Updated: 2026/02/02 04:16:58 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	compile(void *vcoder)
{
}

static void	debug(void *vcoder)
{
}

static void	refactor(void *vcoder)
{
}

void	*coder_job(void *args)
{
	while (1)
	{
		compile(args);
		debug(args);
		refactor(args);
	}
}
