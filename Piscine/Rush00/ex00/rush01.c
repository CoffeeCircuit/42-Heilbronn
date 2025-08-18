/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlayer <jlayer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 09:26:27 by jlayer            #+#    #+#             */
/*   Updated: 2025/08/03 22:07:00 by jlayer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char	g_symbols[8];
void		ft_putchar(char *rect_symbols, int symbol_type);
void		ft_putstr(char *str, int len);

//Writes a top line using the Symbols stored in g_symbols according User Option.
void	ft_top(int x)
{
	int	pos_x;

	pos_x = 1;
	while (pos_x <= x)
	{
		if (pos_x == 1)
			ft_putchar(g_symbols, 0);
		else if (pos_x == x)
			ft_putchar(g_symbols, 1);
		else
			ft_putchar(g_symbols, 4);
		pos_x++;
	}
}

//Writes a mid line using the Symbols stored in g_symbols according User Option.
void	ft_mid(int x)
{
	int	pos_x;

	pos_x = 1;
	while (pos_x <= x)
	{
		if (pos_x == 1)
			ft_putchar(g_symbols, 5);
		else if (pos_x == x)
			ft_putchar(g_symbols, 5);
		else
			ft_putchar(g_symbols, 6);
		pos_x++;
	}
}

//Writes a bot line using the Symbols stored in g_symbols according User Option.
void	ft_bottom(int x)
{
	int	pos_x;

	pos_x = 1;
	while (pos_x <= x)
	{
		if (pos_x == 1)
			ft_putchar(g_symbols, 2);
		else if (pos_x == x)
			ft_putchar(g_symbols, 3);
		else
			ft_putchar(g_symbols, 4);
		pos_x++;
	}
}

//Gets the length and width from start Options.
//An Info will be printed if the User choose 0 length or width.
//Else it will start to write the Rectangle to Terminal.
void	rush(int x, int y)
{
	int	pos_y;

	pos_y = 1;
	if (x == 0 || y == 0)
		ft_putstr("Info: Nothing to print\n", 23);
	else
	{
		while (pos_y <= y)
		{
			if (pos_y == 1)
				ft_top(x);
			else if (pos_y == y)
				ft_bottom(x);
			else
				ft_mid(x);
			ft_putstr("\n", 1);
			pos_y++;
		}
	}
}
