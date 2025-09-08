/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:28:59 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 18:02:26 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/*Checks whether the given delimiter string contains an even number of quotes.
Used to detect syntax errors and determine if quotes were used.*/
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

/*Performs variable expansion within a heredoc line.
If there is no expansion needed -
appends a single character c to the end of a given string s.*/
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

static void	read_heredoc_content(int write_fd, char
		*delimiter, char **env, int ex_code, int quotes_num)
{
	char	*heredoc_content;

	while (1)
	{
		heredoc_content = readline("> ");
		if (!heredoc_content)
		{
			printf(ERR_SIGNAL, delimiter);
			break ;
		}
		if (ft_strcmp(heredoc_content, delimiter) == 0)
		{
			free(heredoc_content);
			break ;
		}
		if (ft_strchr(heredoc_content, '$') && quotes_num == 0)
			heredoc_content = exp_in_heredoc(heredoc_content, env, ex_code);
		write(write_fd, heredoc_content, ft_strlen(heredoc_content));
		write(write_fd, "\n", 1);
		free(heredoc_content);
	}
}

/*Handles heredoc input from the user until the delimiter is reached.
Expands variables in the heredoc input only if the delimiter is unquoted.
Writes the accumulated heredoc content into a pipe.*/
static int	handle_heredoc(int *fd_in, char *delimiter, char **env, t_shell *sh)
{
	int		pipe_fd[2];
	int		quotes_num;
	char	*temp;
	pid_t	pid;
	int		status;

	quotes_num = check_quotes(delimiter);
	if (quotes_num < 0)
		return (0);
	if (pipe(pipe_fd) == -1)
		return (sys_error("parser", "pipe"));
	temp = ft_strtrim(delimiter, " \"\'");
	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]),
			free(temp), sys_error("parser", "fork"));
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigs);
		close(pipe_fd[0]);
		read_heredoc_content(pipe_fd[1], temp, env, sh->exit_code, quotes_num);
		close(pipe_fd[1]);
		free_resources(sh->input, sh->cmds_array, sh->cmd_count,
			&sh->first_token);
		free_array(sh->global_env);
		free(temp);
		free(delimiter);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	close(pipe_fd[1]);
	free(temp);
	waitpid(pid, &status, 0);
	setup_interactive_sigs();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(pipe_fd[0]), 0);
	*fd_in = pipe_fd[0];
	return (1);
}


/*Checks the redirection types (input, output, append, heredoc) and opens the
 corresponding files. Updates the file descriptors (fd_in, fd_out)
 in the command structure. Also checks for errors if there is redirection
 but without filename*/
int	in_out_redir(t_command *cmd, t_token **current_token,
		char **env, t_shell *sh)
{
	int		current_type;
	char	*temp_value;

	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		return (error_input(ERR_SYNTAX_T, 0));
	current_type = (*current_token)->type;
	*current_token = (*current_token)->next;
	temp_value = (*current_token)->value;
	(*current_token)->value = quotes_token((*current_token)->value, env, sh->exit_code);
	if (current_type == TOKEN_REDIR_IN)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (!open_file(cmd, (*current_token)->value, current_type))
		{
			while ((*current_token)->next
				&& (*current_token)->next->type != TOKEN_PIPE)
			{
				*current_token = (*current_token)->next;
				if ((*current_token)->type == TOKEN_HEREDOC)
				{
					free(temp_value);
					*current_token = (*current_token)->next;
					//(*current_token)->value = quotes_token((*current_token)->value, env, sh->exit_code);
					if (!handle_heredoc(&cmd->fd_in, (*current_token)->value, env, sh))
						return (0);
				}
			}
			cmd->fd_in = -1;
			return (-1);
		}
	}
	else if (current_type == TOKEN_REDIR_OUT || current_type == TOKEN_APPEND)
	{
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		if (!open_file(cmd, (*current_token)->value, current_type))
		{
			cmd->fd_out = -1;
			return (-1);
		}
	}
	else if (current_type == TOKEN_HEREDOC)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (!handle_heredoc(&cmd->fd_in, temp_value, env, sh))
			return (0);
	}
	free(temp_value);
	return (1);
}
