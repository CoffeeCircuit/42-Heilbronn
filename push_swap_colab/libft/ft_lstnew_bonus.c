/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:56:51 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/13 19:59:51 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*entry;

	entry = ft_calloc(1, sizeof(t_list));
	if (entry == NULL)
		return (NULL);
	entry->content = content;
	entry->next = NULL;
	return (entry);
}
