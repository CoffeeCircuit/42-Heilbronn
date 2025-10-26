/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 16:56:52 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/26 17:53:59 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	free_buf(t_buffer *buf)
{
	free(buf->data);
	buf->data = NULL;
	buf->len = 0;
	buf->capacity = 0;
	return (0);
}

static int	ensure_capacity(t_buffer *buf, size_t required)
{
	size_t	new_capacity;
	char	*new_data;

	if (required <= buf->capacity)
		return (1);
	new_capacity = buf->capacity;
	while (new_capacity < required)
		new_capacity += CHUNK;
	new_data = (char *)malloc(new_capacity);
	if (new_data == NULL)
		return (0);
	if (buf->data && buf->len > 0)
		ft_memmove(new_data, buf->data, buf->len);
	free(buf->data);
	buf->data = new_data;
	buf->capacity = new_capacity;
	return (1);
}

static int	read_into_buffer(t_buffer *buf, int fd)
{
	ssize_t	bread;
	char	*tmp;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (tmp == NULL)
		return (0);
	while (ft_memchr(buf->data, '\n', buf->len) == NULL)
	{
		bread = read(fd, tmp, BUFFER_SIZE);
		if (bread < 0 || !ensure_capacity(buf, buf->len + bread + 1))
			return (free(tmp), free_buf(buf));
		if (bread == 0)
			break ;
		ft_memmove(buf->data + buf->len, tmp, bread);
		buf->len += bread;
	}
	free(tmp);
	if (buf->len > 0)
		return (1);
	return (0);
}

static char	*extract_line(t_buffer *buf)
{
	char	*newline;
	char	*line;
	size_t	line_len;

	newline = ft_memchr(buf->data, '\n', buf->len);
	if (newline != NULL)
		line_len = (size_t)(newline - buf->data + 1);
	else
		line_len = buf->len;
	line = (char *)malloc(line_len + 1);
	if (line == NULL)
		return (NULL);
	ft_memmove(line, buf->data, line_len);
	line[line_len] = '\0';
	if (newline != NULL)
		ft_memmove(buf->data, newline + 1, buf->len - line_len);
	else if (buf->len > 0)
		buf->data[0] = '\0';
	buf->len -= line_len;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf.data == NULL)
	{
		buf.capacity = CHUNK;
		buf.data = (char *)ft_calloc(buf.capacity, sizeof(char));
		if (buf.data == NULL)
			return (NULL);
	}
	if (!read_into_buffer(&buf, fd))
	{
		if (buf.data != NULL)
			free_buf(&buf);
		return (NULL);
	}
	line = extract_line(&buf);
	if (line == NULL || buf.len == 0)
		free_buf(&buf);
	return (line);
}
