/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-07 10:28:59 by dtimofee          #+#    #+#             */
/*   Updated: 2025-08-07 10:28:59 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/*Checks the redirection types (input, output, append) and opens the
 corresponding files. Updates the file descriptors (fd_in, fd_out)
 in the command structure. Also checks for errors if there is redirection
 but without filename*/
int	in_out_redir(t_command *cmd, t_token **current_token)
{
	int	current_type;

	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		return (error_input(ERR_SYNTAX_T, 0));
	current_type = -1;
	if ((*current_token)->type == TOKEN_REDIR_IN)
	{
		current_type = (*current_token)->type;
		*current_token = (*current_token)->next;
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
	}
	else if ((*current_token)->type == TOKEN_REDIR_OUT
		|| (*current_token)->type == TOKEN_APPEND)
	{
		current_type = (*current_token)->type;
		*current_token = (*current_token)->next;
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
	}
	if (!open_file(cmd, (*current_token)->value, current_type))
		return (0);
	return (1);
}

