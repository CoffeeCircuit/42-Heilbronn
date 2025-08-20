/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalcu <abalcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:26:25 by abalcu            #+#    #+#             */
/*   Updated: 2025/08/20 16:03:27 by abalcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CAT_H
# define FT_CAT_H

# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# define BUF_SIZE 29696

void	ft_zero_buf(char *buf, int size);
int		ft_strlen(const char *str);
int		ft_write(int file, char *app_path, char *file_path);
char	*ft_strcat(char *dest, const char *src);
void	ft_perror(char *app_path, char *file_path, int err);
int		ft_repl(void);
#endif
