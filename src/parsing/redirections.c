/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:28:59 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/09 14:04:43 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/*Checks the redirection types (input, output, append, heredoc) and opens the
 corresponding files. Updates the file descriptors (fd_in, fd_out)
 in the command structure. Also checks for errors if there is redirection
 but without filename*/

int	handle_out_append(t_command *cmd, int current_type,
		char *expanded_file)
{
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	if (!open_file(cmd, expanded_file, current_type))
	{
		cmd->fd_out = -1;
		return (-1);
	}
	return (1);
}

int	handle_redir_heredoc(t_command *cmd, char **delimiter, t_shell *sh)
{
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (!handle_heredoc(&cmd->fd_in, *delimiter, sh))
	{
		free(*delimiter);
		return (0);
	}
	free(*delimiter);
	return (1);
}

int	handle_in(t_command *cmd, int current_type,
		t_token **current_token, t_shell *sh)
{
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (!open_file(cmd, (*current_token)->value, current_type))
	{
		if (!check_for_heredocs(current_token, cmd, sh))
			return (0);
		cmd->fd_in = -1;
		return (-1);
	}
	return (1);
}

int	in_out_redir(t_command *cmd, t_token **current_token,
		t_shell *sh)
{
	int		current_type;
	char	*temp_value;

	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		return (error_input(ERR_SYNTAX_T, 0));
	current_type = (*current_token)->type;
	*current_token = (*current_token)->next;
	temp_value = (*current_token)->value;
	(*current_token)->value = quotes_token((*current_token)->value,
			sh->global_env, sh->exit_code);
	if (current_type == TOKEN_HEREDOC)
		return (handle_redir_heredoc(cmd, &temp_value, sh));
	free(temp_value);
	if (current_type == TOKEN_REDIR_OUT || current_type == TOKEN_APPEND)
		return (handle_out_append(cmd, current_type, (*current_token)->value));
	else if (current_type == TOKEN_REDIR_IN)
		return (handle_in(cmd, current_type, current_token, sh));
	return (1);
}

int	handle_redirections(t_command *cmd, t_token **start, t_shell *sh)
{
	int	return_from_redirections;

	return_from_redirections = in_out_redir(cmd, start, sh);
	if (return_from_redirections == 0)
	{
		cmd->exit_code = 130;
		free_commands(cmd, count_cmd_num(sh->first_token));
		return (0);
	}
	else if (return_from_redirections == -1)
	{
		cmd->exit_code = 1;
		while ((*start)->next && (*start)->next->type != TOKEN_PIPE)
			*start = (*start)->next;
		return (-1);
	}
	return (1);
}
