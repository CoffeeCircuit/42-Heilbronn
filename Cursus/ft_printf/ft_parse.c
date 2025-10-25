/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:56:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/21 07:11:24 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*ft_flag(t_format *fmt, char **s)
{
	unsigned int	bitmask;
	int				l;

	l = 0;
	bitmask = (1 << 1) | (1 << 4) | (1 << 12) | (1 << 14) | (1 << 17);
	while ((*s)[l] >= 32 && (*s)[l] <= 48 && bitmask & (1 << ((*s)[l] - 31)))
	{
		if (l > 5 || strchr(fmt->flags, **s))
			return (NULL);
		fmt->flags[l] = (*s)[l];
		l++;
	}
	fmt->flags[l] = '\0';
	*s += l;
	return (*s);
}

char	*ft_width(t_format *fmt, va_list args, char **s)
{
	if (**s == '*')
	{
		fmt->width = va_arg(args, int);
		(*s)++;
	}
	else if (ft_isdigit(**s))
	{
		fmt->width = ft_atoi(*s);
		*s += ft_strlen(ft_itoa(fmt->width));
	}
	return (*s);
}

char	*ft_spec(t_format *fmt, char **s)
{
	unsigned long long	bitmask;

	bitmask = 9965940738;
	if (**s >= 88 && **s <= 120 && bitmask & (1 << (**s - 87)))
	{
		fmt->spec = **s;
		(*s)++;
	}
	return (*s);
}

void	ft_validate_flags(t_format *fmt)
{
	int	i;

	i = 0;
	fmt->isvalid = 1;
	while (fmt->flags[i])
	{
		if (fmt->spec == 'c' && !((VALID_CS) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		if (fmt->spec == 's' && !((VALID_CS) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		if (fmt->spec == 'u' && !((VALID_U) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		if (fmt->spec == 'p' && !((VALID_P) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		if (fmt->spec == 'h' && !((VALID_H) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		if (fmt->spec == 'd' && !((VALID_DI) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		if (fmt->spec == 'i' && !((VALID_DI) & (1 << (fmt->flags[i] - 31))))
			fmt->isvalid = 0;
		break ;
		i++;
	}
}

t_format	*ft_parse(char *str, va_list args)
{
	t_format	*out;

	out = ft_calloc(1, sizeof(t_format));
	if (!out)
		return (NULL);
	ft_flag(out, &str);
	ft_width(out, args, &str);
	ft_spec(out, &str);
	ft_validate_flags(out);
	if (!out->isvalid)
		return (NULL);
	return (out);
}


