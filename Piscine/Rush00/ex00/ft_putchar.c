/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:36:29 by jlayer            #+#    #+#             */
/*   Updated: 2025/08/03 20:01:29 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// used to copy strings
void	ft_strcpy(char *out, char *in)
{
	while (*in)
	{
		*out = *in;
		out++;
		in++;
	}
	out -= 6;
}

// used to populate the list
void	ft_set_lst(char list_of_strings[5][8], int index, char *str)
{
	int	str_index;

	str_index = 0;
	while (*str)
	{
		list_of_strings[index][str_index] = *str;
		str_index++;
		str++;
	}
	list_of_strings[index][7] = '\0';
}

// sets the out_str to the symbols from the rush no
// by creating a temp list of strings
// uses ft_set_lst to populate the lis
// and then copys the string from the list into the out_string
void	ft_set_symbols(char *out_str, int rush_no)
{
	char	list_of_symbols[5][8];

	ft_set_lst(list_of_symbols, 0, "oooo-| ");
	ft_set_lst(list_of_symbols, 1, "/\\\\/** ");
	ft_set_lst(list_of_symbols, 2, "AACCBB ");
	ft_set_lst(list_of_symbols, 3, "ACACBB ");
	ft_set_lst(list_of_symbols, 4, "ACCABB ");
	ft_strcpy(out_str, list_of_symbols[rush_no]);
}

// symbol_types:
// 0	ltc			left top corner symbol
// 1	rtc			right top corner symbol
// 2	lbc			left bottom corner symbol
// 3	rbc			right bottom corner symbol
// 4	line		horizontal symbol
// 5	col			vertical symbol
// 6 	<space>		space char
// 7 	NULL		null-byte to terminate the string
void	ft_putchar(char *rect_symbols, int symbol_type)
{
	rect_symbols += symbol_type;
	write(1, rect_symbols, 1);
	rect_symbols -= symbol_type;
}

void	ft_putstr(char *str, int len)
{
	write(1, str, len);
}
