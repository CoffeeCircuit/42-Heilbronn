/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 14:20:40 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/11 17:53:59 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*address;
	size_t	total_size;

	if (nmemb != 0 && size != 0)
		if (nmemb > SIZE_MAX / 2 || size > SIZE_MAX / 2)
			return (NULL);
	total_size = nmemb * size;
	address = malloc(total_size);
	if (address == NULL)
		return (NULL);
	if (total_size != 0)
		ft_bzero(address, total_size);
	return (address);
}
