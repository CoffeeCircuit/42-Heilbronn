/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 02:39:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/24 06:50:30 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_has_nl(char **line, char **data)
{
	char	*nl;
	char	*tmp;
	int		nl_len;

	nl = ft_strchr(*data, '\n');
	if (nl)
	{
		nl_len = ft_strlen(nl + 1);
		*line = (char *)malloc(nl - *data + 2);
		if (!(*line))
			return (0);
		(*line)[nl - *data + 1] = '\0';
		ft_memcpy(*line, *data, nl - *data + 1);
		tmp = (char *)malloc(nl_len + 1);
		tmp[nl_len] = '\0';
		ft_memcpy(tmp, nl + 1, nl_len);
		free(*data);
		*data = tmp;
		return (1);
	}
	return (0);
}

char	*ft_append(char *data, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(data, buf);
	free(data);
	return (tmp);
}

char	*ft_read_err(char **data, char **buf, ssize_t *bread)
{
	char	*tmp;

	if (*bread <= 0)
	{
		if (*bread == 0 && *data && **data)
		{
			tmp = ft_strdup(*data);
			free(*data);
			*data = NULL;
			free(*buf);
			return (tmp);
		}
		free(*data);
		*data = NULL;
		free(*buf);
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*data;
	char		*buf;
	char		*line;
	ssize_t		bread;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		if (data && ft_has_nl(&line, &data))
			break ;
		bread = read(fd, buf, BUFFER_SIZE);
		line = ft_read_err(&data, &buf, &bread);
		if (line || bread <= 0)
			return (line);
		buf[bread] = '\0';
		if (!data)
			data = ft_strdup(buf);
		else
			data = ft_append(data, buf);
	}
	free(buf);
	return (line);
}
