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
			return (sys_error("parser", file));
	}
	else if (i == 3)
	{
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (cmd->fd_out == -1)
			return (sys_error("parser", file));
	}
	else if (i == 4)
	{
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (cmd->fd_out == -1)
			return (sys_error("parser", file));
	}
	return (1);
}

/*Checks whether the given delimiter string contains an even number of quotes.
Used to detect syntax errors and determine if quotes were used.*/
int	check_quotes(char *delimiter)
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

int	check_for_heredocs(t_token **current_token, t_command *cmd,
	t_shell *sh)
{
	while ((*current_token)->next
		&& (*current_token)->next->type != TOKEN_PIPE)
	{
		*current_token = (*current_token)->next;
		if ((*current_token)->type == TOKEN_HEREDOC)
		{
			*current_token = (*current_token)->next;
			if (!handle_heredoc(&cmd->fd_in, (*current_token)->value, sh))
				return (0);
		}
	}
	return (1);
}
