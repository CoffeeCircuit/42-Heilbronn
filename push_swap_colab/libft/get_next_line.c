/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:48:11 by mawelsch          #+#    #+#             */
/*   Updated: 2025/11/07 15:29:24 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

void	ft_bzero(void *s, size_t n);
int		ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

void	get_new_left(int index_2, char *left, int index, char *total)
{
	int	index_left;

	index_left = 0;
	while (total[index_2] != '\0')
		index_2++;
	if (index_2 > (index + 1) && total[index] != '\0')
	{
		while (index_2 >= ++index)
		{
			left[index_left] = total[index];
			index_left++;
		}
	}
	else
		ft_bzero(left, BUFFER_SIZE + 1);
}

char	*end_nl(char *total, char *left, char *buffer)
{
	int		index;
	int		index_2;
	char	*retstr;

	index = 0;
	index_2 = 0;
	while (total[index] != '\n' && total[index] != '\0')
		index++;
	retstr = malloc(index + 2);
	if (retstr == NULL)
	{
		ft_bzero(left, BUFFER_SIZE + 1);
		return (NULL);
	}
	while (index_2 <= index)
	{
		retstr[index_2] = total[index_2];
		index_2++;
	}
	retstr[index_2] = '\0';
	get_new_left(index_2, left, index, total);
	free(total);
	total = NULL;
	free(buffer);
	return (retstr);
}

char	*book_burner(int bytes_read, char *buffer, char *left, char *total)
{
	char	*tmp;

	if (bytes_read == -1)
	{
		ft_bzero(left, BUFFER_SIZE + 1);
		free(buffer);
		return (NULL);
	}
	if (bytes_read == 0)
	{
		free(buffer);
		if (total[0] != '\0')
			tmp = ft_strjoin("", total);
		else
			tmp = NULL;
		free(total);
		ft_bzero(left, BUFFER_SIZE + 1);
		return (tmp);
	}
	return (NULL);
}

char	*librarian(int fd, char *buffer, char *left, char *total)
{
	int		bytes_read;
	char	*tmp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1 || bytes_read == 0)
			return (book_burner(bytes_read, buffer, left, total));
		buffer[bytes_read] = '\0';
		if (total != NULL)
		{
			tmp = ft_strjoin(total, buffer);
			if (tmp == NULL)
				return (NULL);
			free(total);
			total = tmp;
		}
		else
			total = ft_strjoin("", buffer);
		if (ft_strchr(buffer, '\n') != NULL)
			return (end_nl(total, left, buffer));
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*total;
	static char	left[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		ft_bzero(left, BUFFER_SIZE + 1);
		return (NULL);
	}
	total = ft_strjoin("", left);
	if (total == NULL)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		ft_bzero(left, BUFFER_SIZE + 1);
		free(total);
		return (NULL);
	}
	if (total != NULL)
		if (ft_strchr(total, '\n') != NULL)
			return (end_nl(total, left, buffer));
	return (librarian(fd, buffer, left, total));
}
