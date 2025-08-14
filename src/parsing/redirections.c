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

static int	check_quotes(char *delimiter)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (*delimiter)
	{
		if (*delimiter == '"')
			double_quotes++;
		else if (*delimiter == '\'')
			single_quotes++;
		delimiter++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		return (error_input(ERR_SYNTAX_T, -1));
	return (single_quotes + double_quotes);
}

static char	*exp_in_heredoc(char *str, char **env, int ex_code)
{
	char	*start;
	char	*new_str;

	start = str;
	new_str = ft_strdup("");
	while (*start)
	{
		if (*start == '$' && (ft_isalnum(*(start + 1))
				|| *(start + 1) == '_' || *(start + 1) == '?'))
		{
			start++;
			if (*start == '?')
			{
				new_str = ft_strjoin(new_str, ft_itoa(ex_code));
				start++;
			}
			else
				new_str = do_expansion(&start, env, ex_code, new_str);
		}
		else
		{
			new_str = ft_strjoin_char(new_str, *start);
			start++;
		}
	}
	free (str);
	return (new_str);
}

static int	handle_heredoc(int *fd_in, char *delimiter, char **env, int ex_code)
{
	char	*heredoc_content;
	int		pipe_fd[2];
	int		quotes_num;
	char	*temp;

	quotes_num = check_quotes(delimiter);
	if (quotes_num < 0)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (sys_error("parser", "pipe"));
	temp = ft_strtrim(delimiter, " \"\'");
	free(delimiter);
	delimiter = temp;
	while (1)
	{
		heredoc_content = readline("> ");
		if (!heredoc_content || ft_strcmp(heredoc_content, delimiter) == 0)
			break ;
		if (ft_strchr(heredoc_content, '$') && quotes_num == 0)
			heredoc_content = exp_in_heredoc(heredoc_content, env, ex_code);
		write(pipe_fd[1], heredoc_content, ft_strlen(heredoc_content));
		write(pipe_fd[1], "\n", 1);
		free(heredoc_content);
	}
	free(heredoc_content);
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
	*current_token = (*current_token)->next;
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
		if (!handle_heredoc(&cmd->fd_in, (*current_token)->value, env, ex_code))
			return (0);
	}
	return (1);
}

