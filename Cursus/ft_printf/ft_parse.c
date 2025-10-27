/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:56:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 18:42:31 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_flags(char **s, t_format *fmt)
{
	const char	*flags = "+-0 #";

	while (**s && strchr(flags, **s))
	{
		if (**s == '-')
			fmt->has_minus = 1;
		else if (**s == '+')
			fmt->has_plus = 1;
		else if (**s == ' ')
			fmt->has_space = 1;
		else if (**s == '0')
			fmt->has_zero = 1;
		else if (**s == '#')
			fmt->has_hash = 1;
		(*s)++;
	}
}

void	ft_parse_width(char **s, t_format *fmt)
{
	int	nbr;

	nbr = 0;
	while (**s && isdigit(**s))
	{
		nbr = nbr * 10 + (**s - '0');
		(*s)++;
	}
	fmt->width = nbr;
}

int	ft_validate_flags(t_format *fmt)
{
	char	sp;

	sp = fmt->specifier;
	if (sp == 'c' || sp == 's' || sp == '%')
		return (!(fmt->has_plus || fmt->has_space || fmt->has_hash
				|| fmt->has_zero));
	if (sp == 'p')
		return (!(fmt->has_plus || fmt->has_space));
	if (sp == 'd' || sp == 'i')
		return (1);
	if (sp == 'u')
		return (!(fmt->has_plus || fmt->has_space));
	if (sp == 'x' || sp == 'X')
		return (1);
	return (0);
}

void	ft_parse_spec(char **s, t_format *fmt)
{
	const char	*specs = "cspdiuxX%";

	if (**s && strchr(specs, **s))
	{
		fmt->specifier = **s;
		fmt->is_valid = ft_validate_flags(fmt);
	}
	(*s)++;
}
