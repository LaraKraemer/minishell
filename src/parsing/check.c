/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:40:53 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/02 18:47:53 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

int	is_last_token_word(t_token *first_token)
{
	t_token	*last_token;

	last_token = ms_lstlast(first_token);
	if (last_token->type == TOKEN_WORD)
		return (1);
	return (0);
}

int	open_file(t_command *cmd, char *file, int i)
{
	if (i == 2)
	{
		cmd->fd_in = open(file, O_RDONLY);
		if (cmd->fd_in == -1)
		{
			// if (!cmd->redir_err_flag)
			// {
				sys_error("parser", file);
				//cmd->redir_err_flag = 1;
			//}
			return (0);
		}
	}
	else if (i == 3)
	{
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		//printf("%d - out_fd in open file\n", cmd->fd_out);
		if (cmd->fd_out == -1)
		{
			sys_error("parser", file);
			return (0);
		}
	}
	else if (i == 4)
	{
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (cmd->fd_out == -1)
		{
			sys_error("parser", file);
			return (0);
		}
	}
	return (1);
}
