/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mawelsch <mawelsch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 22:40:26 by mawelsch          #+#    #+#             */
/*   Updated: 2025/10/14 16:03:23 by mawelsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void	*content);
void	ft_lstclear(t_list **lst, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*first_node_new_list;
	void	*content;

	first_node_new_list = NULL;
	while (lst != NULL)
	{
		if (f != NULL)
		{
			content = f(lst->content);
			new = ft_lstnew(content);
		}
		else
			return (NULL);
		if (new == NULL)
		{
			del(content);
			ft_lstclear(&first_node_new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&first_node_new_list, new);
		lst = lst->next;
	}
	return (first_node_new_list);
}
