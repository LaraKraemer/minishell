/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:44:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 11:38:48 by 123              ###   ########.fr       */
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

int	ms_lstclear(t_token **first_token)
{
	t_token	*next;

	if (first_token == NULL || *first_token == NULL)
		return (0);
	while (*first_token != NULL)
	{
		next = (*first_token)->next;
		free((*first_token)->value);
		free(*first_token);
		*first_token = next;
	}
	*first_token = NULL;
	return (1);
}
