/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 08:56:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/19 14:41:42 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_flag(t_spec *f, char **str)
{
	int	i;

	i = 0;
	f->flags = ft_calloc(6, sizeof(char));
	if (!(f->flags))
		return (NULL);
	while (**str >= 32 && **str <= 48 && 151571U >> (**str - 31) & 1)
	{
		ft_memset(&f->flags[i], **str, 1);
		(*str)++;
		i++;
	}
	return (*str);
}

char	*ft_width(t_spec *f, char **str)
{
	if (**str == '*')
	{
		f->width = -1;
		(*str)++;
	}
	else if (ft_isdigit(**str))
	{
		f->width = ft_atoi(*str);
		*str = *str + ft_strlen(ft_itoa(f->width));
	}
	return (*str);
}

int	ft_isvalid(char s, char *f)
{
	if ((s == 'c' || s == 's') && ft_strlen(f) <= 1 && (*f == '-'
			|| *f == '\0'))
		return (1);
	if ((s == 'd' || s == 'i') && !(ft_strchr(f, '#')))
		return (1);
	if ((s == 'x' || s == 'X'))
		return (1);
	return (0);
}

char	*ft_spec(t_spec *f, char **str)
{
	if (**str >= 88 && **str <= 120 && 9965940739ULL >> (**str - 87) & 1)
	{
		f->specifier = **str;
		(*str)++;
	}
	if (!(ft_isvalid(f->specifier, f->flags)))
	{
		f->specifier = '\0';
		return (NULL);
	}
	return (*str);
}

t_spec	*ft_parse(char *str)
{
	t_spec	*out;

	out = ft_calloc(1, sizeof(t_spec));
	if (!out)
		return (NULL);
	ft_flag(out, &str);
	ft_width(out, &str);
	ft_spec(out, &str);
	out->position = &(*str);
	if (!out->specifier)
		return (NULL);
	return (out);
}

void	ft_puthex(int nbr, t_spec *fmt)
{
	const char	*lc_base = "0123456789abcdef";
	const char	*uc_base = "0123456789ABCDEF";
	long long	n;

	n = (long long)nbr;
	if (n == 0)
		return ;
	if (nbr < 0)
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		n = -n;
	}
	ft_puthex(n / 16, fmt);
	if (fmt->specifier == 'x')
		ft_putchar_fd(lc_base[n % 16], STDOUT_FILENO);
	else if (fmt->specifier == 'X')
		ft_putchar_fd(uc_base[n % 16], STDOUT_FILENO);
}

void	ft_putarg(t_spec *spec, va_list args)
{
	if (spec->specifier == 'c')
		ft_putchar_fd(va_arg(args, int), STDOUT_FILENO);
	else if (spec->specifier == 's')
		ft_putstr_fd(va_arg(args, char *), STDOUT_FILENO);
	else if (spec->specifier == 'x' || spec->specifier == 'X')
		ft_puthex(va_arg(args, int), spec);
}

void	ft_clear_spec(t_spec *spec)
{
	free(spec->flags);
	spec->flags = NULL;
	spec->width = 0;
	spec->specifier = '\0';
	spec->position = NULL;
	free(spec);
	spec = NULL;
}

int	ft_printf(const char *format, ...)
{
	int		len;
	va_list	args;
	t_spec	*spec;
	char	*str;

	len = 0;
	str = (char *)format;
	va_start(args, format);
	while (str[len])
	{
		if (str[len] == '%')
		{
			spec = ft_parse(&str[++len]);
			ft_putarg(spec, args);
			len += spec->position - &str[len];
			ft_clear_spec(spec);
		}
		else
			ft_putchar_fd(str[len++], STDOUT_FILENO);
	}
	va_end(args);
	return (len);
}

int	main(void)
{
	ft_printf("test: %c, %c\n", 'a', 'b');
	ft_printf("test: %s\n", "foo");
	ft_printf("test: %x\n", 255);
	ft_printf("test: %X\n", 255);
}
