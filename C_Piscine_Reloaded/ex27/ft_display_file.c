/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:10:48 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/07 17:37:14 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#define BUF_SIZE 4096

int	ft_print_file(char *path)
{
	int		fd;
	char	buf[BUF_SIZE];
	ssize_t	bread;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	bread = read(fd, buf, BUF_SIZE - 1);
	if (bread == -1)
		return (1);
	while (bread)
	{
		write(STDOUT_FILENO, buf, bread);
		bread = read(fd, buf, BUF_SIZE - 1);
	}
	close(fd);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	read_ok;

	read_ok = 0;
	if (argc == 1)
		write(STDERR_FILENO, "File name missing.\n", 19);
	else if (argc > 2)
		write(STDERR_FILENO, "Too many arguments.\n", 20);
	else
	{
		read_ok = ft_print_file(argv[1]);
		if (read_ok == 1)
		{
			write(STDERR_FILENO, "Cannot read file.\n", 18);
			return (1);
		}
	}
	return (0);
}
