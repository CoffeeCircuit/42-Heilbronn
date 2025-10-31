/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:58:43 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/31 04:47:32 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_format
{
	int				width;
	char			specifier;
	unsigned int	is_valid : 1;
	unsigned int	has_plus : 1;
	unsigned int	has_minus : 1;
	unsigned int	has_zero : 1;
	unsigned int	has_hash : 1;
	unsigned int	has_space : 1;
}			t_format;

int			ft_printf(const char *format, ...);
void		ft_parse_flags(char **s, t_format *fmt);
void		ft_parse_width(char **s, t_format *fmt);
int			ft_validate_flags(t_format *fmt);
void		ft_parse_spec(char **s, t_format *fmt);
void		ft_init_format(t_format *fmt);
int			ft_dispatch_format(t_format *fmt, va_list args);
int			ft_format_output(char **s, va_list args);
int			ft_write_char(t_format *fmt, int c);
int			ft_write_string(t_format *fmt, char *str);
int			ft_write_int(t_format *fmt, int n);
int			ft_write_unsigned(t_format *fmt, unsigned int n);
int			ft_write_hex(t_format *fmt, unsigned int n, int uppercase);
int			ft_write_pointer(t_format *fmt, void *ptr);
int			ft_nbrlen(long long nbr, int base);
int			ft_write_rec_nbr(unsigned long n, const char *base_chars, int base);
int			ft_write_base(long n, const char *base_chars, int base);
int			ft_write_padding(t_format *fmt, int size);
char		*ft_strchr(const char *s, int c);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);

#endif
