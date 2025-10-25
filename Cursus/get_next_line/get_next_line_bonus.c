/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 02:39:17 by abalcu            #+#    #+#             */
/*   Updated: 2025/10/25 15:37:59 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_read_err(char **data, ssize_t *bread)
{
	char	*tmp;

	if (*bread <= 0)
	{
		if (*bread == 0 && *data && **data)
		{
			tmp = ft_strdup(*data);
			free(*data);
			*data = NULL;
			return (tmp);
		}
		free(*data);
		*data = NULL;
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*data[MAX_FD];
	char		*buf;
	char		*line;
	ssize_t		bread;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		if (data[fd] && ft_has_nl(&line, &data[fd]))
			break ;
		bread = read(fd, buf, BUFFER_SIZE);
		line = ft_read_err(&data[fd], &bread);
		if (line || bread <= 0)
			return (free(buf), line);
		buf[bread] = '\0';
		if (!data[fd])
			data[fd] = ft_strdup(buf);
		else
			data[fd] = ft_append(data[fd], buf);
	}
	free(buf);
	return (line);
}
