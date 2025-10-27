/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:35:33 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/27 14:38:45 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_getnbrlen(size_t nbr, int base)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		len++;
		nbr /= base;
	}
	return (len);
}

char	*ft_make_str(t_format *fmt, unsigned int nbr, int base)
{
	int		strlen;
	int		nbrlen;
	char	*out;

	strlen = 0;
	nbrlen = ft_getnbrlen(nbr, base);
	if ((fmt->spec == 'x' || fmt->spec == 'X') && ft_strchr(fmt->flags, '#'))
		nbrlen += 2;
	if ((fmt->spec == 'd' || fmt->spec == 'i') && ft_strchr(fmt->flags, ' '))
		nbrlen += 1;
	if (fmt->width < nbrlen)
		strlen += fmt->width - nbrlen;
	else
		strlen += fmt->width;
	out = (char *)malloc(strlen + 1);
	out[strlen] = '\0';
	if (ft_strchr(fmt->flags, '0'))
		ft_memset(out, '0', strlen);
	else
		ft_memset(out, ' ', strlen);
	if (!out)
		return (NULL);
	return (out);
}

void	ft_puthex(t_format *fmt, int nbr)
{
	const char		*hex = "0123456789abcdef";
	unsigned int	n;
	int				len;
	char			*out;
	int				nbr_len;

	out = ft_make_str(fmt, (unsigned int)nbr, 16);
	n = (unsigned int)nbr;
	len = 0;
	nbr_len = ft_getnbrlen(n, 16);
	if (ft_strrchr(fmt->flags, '#'))
	{
		ft_memmove(out, "0x", 2);
		nbr_len += 2;
	}
	len = nbr_len;
	if (ft_strrchr(fmt->flags, '-'))
	{
		while (n)
		{
			out[--len] = hex[n % 16];
			n /= 16;
		}
	}
	ft_memset(&out[nbr_len], ' ', fmt->width - nbr_len);
	ft_putstr_fd(out, STDOUT_FILENO);
	free(out);
}

void	ft_putarg(t_format *fmt, va_list args)
{
	if (fmt->spec == 'c')
		ft_putchar_fd(va_arg(args, int), STDOUT_FILENO);
	else if (fmt->spec == 's')
		ft_putstr_fd(va_arg(args, char *), STDOUT_FILENO);
	else if (fmt->spec == 'x' || fmt->spec == 'X')
		ft_puthex(fmt, va_arg(args, int));
}
