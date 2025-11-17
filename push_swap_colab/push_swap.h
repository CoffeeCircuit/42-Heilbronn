/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:13:02 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/16 20:15:58 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"
# include "merge_sort.h"

typedef enum e_strat
{
	ADAPTIVE,
	SIMPLE,
	MEDIUM,
	COMPLEX,
}			t_strat;

typedef struct s_flag
{
	t_strat	strategy;
	int		strat_set;
	int		bench_set;
	int		valid_flag;
}			t_flag;

typedef struct s_stat
{
	size_t	ops;
	size_t	s[2];
	size_t	p[2];
	size_t	r[2];
	size_t	rr[2];
	size_t	ss;
	size_t	rr_;
	size_t	rrr;
	double	disorder;
	t_strat	strategy;
	int		size_a;
	int		size_b;
}			t_stat;

typedef struct s_stk
{
	t_stat	*sts;
	t_flag	*flgs;
	int		*vals;
	size_t	len;
	size_t	cap;
	char	name;
}			t_stk;

int		parse_bench(t_flag *flags, char const *arg);
int		parse_strat(t_flag *flags, char const *arg);
int		parse_flag(t_flag *flags, int *pos, int argc, char const *argv[]);
int		parse_numargs(t_stk *stk, int *pos, int argc, char const *argv[]);
int		parse_args_str(t_stk *stk, size_t *len, const char *argv);
float	get_disorder(int *stack, int size);
int		contains(int *arr, int nbr, size_t len);
int		is_num(char const *arg);
void	pbench(t_stat *sts);
void	perror(void);

void	s(t_stk *stk);
void	ss(t_stk *stk_1, t_stk *stk_2);
void	p(t_stk *to, t_stk *from);
void	r(t_stk *stk);
void	rr(t_stk *stk);
void	rr_(t_stk *stk_1, t_stk *stk_2);
void	rrr(t_stk *stk_1, t_stk *stk_2);

void	swap(int *arr);
void	rotate(int *arr, size_t len);
void	rrotate(int *arr, size_t len);
int		pop(int *arr, size_t *len);
void	push(int val, int *arr, size_t *len);

void	ps_sort(t_stk *a, t_stk *b);

void	small_merger(t_stk *a, t_stk *b, t_lists *lsts);
void	big_merger(t_stk *a, t_stk *b, t_lists *lsts);

void	simple_sort(t_stk *a, t_stk *b);
void	medium_sort(t_stk *a, t_stk *b);
void	complex_sort(t_stk *a, t_stk *b);
void	adaptive_sort(t_stk *a, t_stk *b);

size_t	get_first_list_size_a(t_stk *stk);
size_t	get_first_list_size_b(t_stk *stk);
size_t	get_last_list_size_a(t_stk *stk, size_t l1l);
size_t	get_last_list_size_b(t_stk *stk, size_t l1l);

#endif // PUSH_SWAP_H
