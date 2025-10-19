/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:58:43 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/19 13:50:59 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "include/libft.h"
# include <stdarg.h>

typedef struct s_spec
{
	char	*flags;
	int		width;
	char	specifier;
	char 	*out;
	char	*position;
}			t_spec;

int			ft_printf(const char *format, ...);
char		*ft_parse_flag(t_spec *f, char **str);
char		*ft_parse_width(t_spec *f, char **str);
char		*ft_parse_spec(t_spec *f, char **str);
t_spec		*ft_parse_format(char *str);

#endif
