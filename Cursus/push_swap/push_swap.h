/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 23:01:41 by abalcu            #+#    #+#             */
/*   Updated: 2025/11/26 01:26:10 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_stk
{
	int		*vals;
	size_t	len;
	size_t	cap;
	char	name;
}			t_stk;

typedef struct s_limit
{
	int		min;
	int		max;
}			t_limit;

typedef struct s_mcounter
{
	int		i;
	int		p;
}			t_mcounter;

int			ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
char		**ft_split(char const *s, char c);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);

int			parse_numargs(t_stk *stk, int *pos, int argc, char const *argv[]);
int			parse_args_str(t_stk *stk, const char *argv);

int			is_num(char const *arg);
void		ft_perror(void);

void		s(t_stk *stk);
void		ss(t_stk *stk_1, t_stk *stk_2);
void		p(t_stk *to, t_stk *from);
void		r(t_stk *stk);
void		rr(t_stk *stk);
void		rr_(t_stk *stk_1, t_stk *stk_2);
void		rrr(t_stk *stk_1, t_stk *stk_2);

void		swap(int *arr);
void		rotate(int *arr, size_t len);
void		rrotate(int *arr, size_t len);
int			pop(int *arr, size_t *len);
void		push(int val, int *arr, size_t *len);

void		ps_sort(t_stk *a, t_stk *b);

int			max_index(int *a, size_t len);
int			*sort_(int *arr, int len);
int			*val_to_idx(int *arr, int len);
t_limit		*get_chunck_range(int len, int count);
int			find_next_in_chunk(int *arr, int len, t_limit chunk);

#endif // PUSH_SWAP_H
