/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 18:33:12 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/17 02:19:29 by mawelsch         ###   ########.fr       */
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

void	small_merger_list_1(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst);
void	big_merger_list_1(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst);
void	small_merger_list_2(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst);
void	big_merger_list_2(t_stk *a, t_stk *b, t_lists *lsts, int *active_lst);

size_t	get_first_list_size_a(t_stk *stk);
size_t	get_first_list_size_b(t_stk *stk);
size_t	get_last_list_size_a(t_stk *stk, size_t l1l);
size_t	get_last_list_size_b(t_stk *stk, size_t l1l);

void	slide_to_top_bottom_b(t_stk *a, t_stk *b, size_t *list);
void	slide_to_top_bottom_a(t_stk *a, t_stk *b, size_t *list);

void	switch_sublist(t_lists *lsts, t_stk *stk, int *active_list);

#endif //MERGE_SORT_H