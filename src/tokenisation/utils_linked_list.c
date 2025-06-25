/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:44:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/02 17:20:35 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"

t_token	*ms_lstnew(int type, char *value)
{
	t_token	*newnode;

	newnode = malloc(sizeof(t_token));
	if (newnode == NULL)
		return (NULL);
	newnode->type = type;
	newnode->value = value;
	newnode->next = NULL;
	return (newnode);
}

t_token	*ms_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ms_lstadd_back(t_token **lst, t_token *new_node)
{
	t_token	*last;

	if (new_node == NULL)
		return ;
	last = ms_lstlast(*lst);
	last->next = new_node;
}
