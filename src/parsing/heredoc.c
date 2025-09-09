/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:49:18 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/09 13:55:35 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

static char	*need_expansion(char *new_str, char **start,
		char **env, int ex_code)
{
	char	*expanded_str;

	if (**start == '?')
	{
		expanded_str = ft_strjoin(new_str, ft_itoa(ex_code));
		(*start)++;
	}
	else
		expanded_str = do_expansion(start, env, ex_code, new_str);
	return (expanded_str);
}

/*Performs variable expansion within a heredoc line.
If there is no expansion needed -
appends a single character c to the end of a given string s.*/
static char	*exp_in_heredoc(char **str, char **env, int ex_code)
{
	char	*start;
	char	*new_str;

	start = *str;
	new_str = ft_strdup("");
	while (*start)
	{
		if (*start == '$' && (ft_isalnum(*(start + 1))
				|| *(start + 1) == '_' || *(start + 1) == '?'))
		{
			start++;
			new_str = need_expansion(new_str, &start, env, ex_code);
		}
		else
		{
			new_str = ft_strjoin_char(new_str, *start);
			start++;
		}
	}
	free (*str);
	return (new_str);
}

static void	read_heredoc_content(int write_fd, char *delimiter,
		t_shell *sh, int quotes_num)
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
			heredoc_content = exp_in_heredoc(&heredoc_content,
					sh->global_env, sh->exit_code);
		write(write_fd, heredoc_content, ft_strlen(heredoc_content));
		write(write_fd, "\n", 1);
		free(heredoc_content);
	}
}

static int	heredoc_parent(int *pipe_fd, int *fd_in, char *temp, pid_t pid)
{
	int	status;

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

/*Handles heredoc input from the user until the delimiter is reached.
Expands variables in the heredoc input only if the delimiter is unquoted.
Writes the accumulated heredoc content into a pipe.*/
int	handle_heredoc(int *fd_in, char *delimiter, t_shell *sh)
{
	int		pipe_fd[2];
	int		quotes_num;
	char	*temp;
	pid_t	pid;

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
		read_heredoc_content(pipe_fd[1], temp, sh, quotes_num);
		close(pipe_fd[1]);
		free_and_exit(sh, temp, delimiter);
	}
	return (heredoc_parent(pipe_fd, fd_in, temp, pid));
}
