/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:33:12 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/16 18:34:16 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MERGE_SORT_H
# define MERGE_SORT_H
# include "push_swap.h"

typedef struct s_mrg
{
	size_t	full_size;
	size_t	sublist_count;
	size_t	sublist_size;
	int		appended_last_chunk;
}	t_mrg;

typedef struct s_lists
{
	size_t	sublists;
	size_t	l1l;
	size_t	l2l;
	int		must_rotate;
}	t_lists;

#endif //MERGE_SORT_H