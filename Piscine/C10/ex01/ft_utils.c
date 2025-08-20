/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 12:17:37 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/20 15:59:25 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cat.h"

void	ft_zero_buf(char *buf, int size)
{
	short	index;

	index = 0;
	while (index <= size)
	{
		buf[index] = '\0';
		index++;
	}
}

int	ft_strlen(const char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return (0);
	while (str[index])
		index++;
	return (index);
}

int	ft_write(int file, char *app_path, char *file_path)
{
	char	buf[BUF_SIZE];
	ssize_t	bytes_read;

	bytes_read = -1;
	while (bytes_read)
	{
		ft_zero_buf(buf, BUF_SIZE);
		bytes_read = read(file, buf, BUF_SIZE);
		if (bytes_read == -1)
			ft_perror(app_path, file_path, errno);
		write(STDOUT_FILENO, buf, bytes_read);
		return (bytes_read);
	}
	return (0);
}

char	*ft_strcat(char *dest, const char *src)
{
	unsigned int	src_index;
	unsigned int	dest_index;

	src_index = 0;
	dest_index = 0;
	while (dest[dest_index])
		dest_index++;
	while (src[src_index])
	{
		dest[dest_index] = src[src_index];
		src_index++;
		dest_index++;
	}
	dest[dest_index] = '\0';
	return (dest);
}

void	ft_perror(char *app_path, char *file_path, int err)
{
	char	buf[BUF_SIZE];

	ft_zero_buf(buf, BUF_SIZE);
	ft_strcat(buf, basename(app_path));
	ft_strcat(buf, ": ");
	if (file_path)
	{
		ft_strcat(buf, file_path);
		ft_strcat(buf, ": ");
	}
	ft_strcat(buf, strerror(err));
	ft_strcat(buf, "\n");
	write(STDERR_FILENO, buf, ft_strlen(buf));
}
