/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 09:58:43 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/21 05:50:42 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "include/libft.h"
# include <stdarg.h>
# define VALID_CS (1 << 14)
# define VALID_U (1 << 14) | (1 << 17)
# define VALID_P (1 << 14)
# define VALID_H (1 << 4) | (1 << 14) | (1 << 17)
# define VALID_DI (1 << 1) | (1 << 12) | (1 << 14) | (1 << 17)

typedef struct s_format
{
	char	flags[6];
	char	isvalid;
	int		width;
	char	spec;
	char	*position;
}			t_format;

char		*ft_flag(t_format *fmt, char **s);
char		*ft_width(t_format *fmt, char **s);
char		*ft_spec(t_format *fmt, char **s);
void		ft_validate_flags(t_format *fmt);
t_format	*ft_parse(char *str);

#endif
