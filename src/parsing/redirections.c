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

static int	handle_heredoc(int *fd_in, char *delimiter, char **env, int ex_code)
{
	char	*heredoc_content;
	char	*expanded;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (sys_error("parser", "pipe"));
	while (1)
	{
		heredoc_content = readline("> ");
		if (!heredoc_content || ft_strcmp(heredoc_content, delimiter) == 0)
		{
			free(heredoc_content);
			break ;
		}
		expanded = quotes_token(heredoc_content, env, ex_code);
		write(pipe_fd[1], expanded, ft_strlen(expanded));
		write(pipe_fd[1], "\n", 1);
		free(heredoc_content);
		free(expanded);
	}
	close(pipe_fd[1]);
	*fd_in = pipe_fd[0];
	return (1);
}

/*Checks the redirection types (input, output, append) and opens the
 corresponding files. Updates the file descriptors (fd_in, fd_out)
 in the command structure. Also checks for errors if there is redirection
 but without filename*/
int	in_out_redir(t_command *cmd, t_token **current_token,
		char **env, int ex_code)
{
	int	current_type;

	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		return (error_input(ERR_SYNTAX_T, 0));
	current_type = (*current_token)->type;
	// printf("current token type %d\n", current_type);
	// printf("current token value %s\n", (*current_token)->value);
	*current_token = (*current_token)->next;
	//printf("next token value %s\n", (*current_token)->value);
	if (current_type == TOKEN_REDIR_IN)
	{
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		if (!open_file(cmd, (*current_token)->value, current_type))
			return (0);
	}
	else if (current_type == TOKEN_REDIR_OUT || current_type == TOKEN_APPEND)
	{
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
		if (!open_file(cmd, (*current_token)->value, current_type))
			return (0);
	}
	else if (current_type == TOKEN_HEREDOC)
	{
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		//printf("Delimiter %s\n", (*current_token)->value);
		if (!handle_heredoc(&cmd->fd_in, (*current_token)->value, env, ex_code))
			return (0);
	}
	return (1);
}

