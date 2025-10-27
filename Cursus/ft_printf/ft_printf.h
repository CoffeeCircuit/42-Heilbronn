/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:58:43 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 14:34:48 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <ctype.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_format
{
	char			specifier;
	int				width;
	unsigned int	is_valid : 1;
	unsigned int	has_plus : 1;
	unsigned int	has_minus : 1;
	unsigned int	has_zero : 1;
	unsigned int	has_hash : 1;
	unsigned int	has_space : 1;
}			t_format;

void		ft_parse_flags(char **s, t_format *fmt);
void		ft_parse_width(char **s, t_format *fmt);
int			ft_validate_flags(t_format *fmt);
void		ft_parse_spec(char **s, t_format *fmt);
void		ft_init_format(t_format *fmt);
int			ft_format_output(char **s, va_list args);
#endif
