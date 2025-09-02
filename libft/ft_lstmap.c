/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-26 10:52:16 by dtimofee          #+#    #+#             */
/*   Updated: 2024-11-26 10:52:16 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*add_node(t_list *lst, t_list **dest,
		void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	void	*node_content;

	node_content = f(lst->content);
	node = ft_lstnew(node_content);
	if (node == NULL)
	{
		del(node_content);
		ft_lstclear(dest, del);
	}
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*node;
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	dest = NULL;
	while (lst != NULL)
	{
		node = add_node(lst, &dest, f, del);
		if (node == NULL)
			return (NULL);
		if (dest == NULL)
			dest = node;
		else
			last->next = node;
		last = node;
		lst = lst->next;
	}
	return (dest);
}
