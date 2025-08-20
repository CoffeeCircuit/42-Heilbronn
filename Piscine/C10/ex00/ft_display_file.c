/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:37:49 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/20 09:28:55 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF_SIZE 1024

void	ft_zero_buf(char buf[BUF_SIZE])
{
	short	index;

	index = 0;
	while (index++ < BUF_SIZE)
	{
		buf[index] = '\0';
		index++;
	}
}

int	ft_write(int file, char buf[BUF_SIZE], int bytes_read)
{
	while (bytes_read)
	{
		ft_zero_buf(buf);
		bytes_read = read(file, buf, BUF_SIZE);
		if (bytes_read == -1 || file == -1)
		{
			write(STDERR_FILENO, "Cannot read file.", 18);
			return (0);
		}
		write(STDOUT_FILENO, buf, bytes_read);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		file;
	char	buf[BUF_SIZE];
	ssize_t	bytes_read;

	file = -1;
	bytes_read = -1;
	if (argc == 1)
		write(STDERR_FILENO, "File name missing.\n", 19);
	else if (argc > 2)
		write(STDERR_FILENO, "Too many arguments.\n", 20);
	else
	{
		file = open(argv[1], O_RDONLY);
		ft_write(file, buf, bytes_read);
		write(STDOUT_FILENO, "\n", 1);
	}
	close(file);
	return (0);
}
