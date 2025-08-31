/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:15:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025/08/26 22:01:25 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/* 
Filter function for builtin cmd in parent process
*/
int	must_run_in_parent(const char *cmd)
{
	int			i;
	const char	*parent_builtins[5];

	parent_builtins[0] = "cd";
	parent_builtins[1] = "export";
	parent_builtins[2] = "unset";
	parent_builtins[3] = "exit";
	parent_builtins[4] = NULL;
	i = 0;
	while (parent_builtins[i])
	{
		if (ft_strcmp(cmd, parent_builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_commands(t_command *cmds, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (cmds[i].cmd_path)
			free(cmds[i].cmd_path);
		if (cmds[i].cmd_args)
			free_array(cmds[i].cmd_args);
		if (cmds[i].path_file)
			free_array(cmds[i].path_file);
		if (cmds[i].env)
			free_array(cmds[i].env);
		i++;
	}
	free(cmds);
}

void	free_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		free (str_array[i++]);
	free (str_array);
}

/* 
Initializes pipe file descriptors for command pipeline 
Allocates (cmd_count-1)*2 file descriptors in pipe_fds
*/
int	setup_pipes(int cmd_count, int **pipe_fds)
{
	int	i;

	i = 0;
	if (cmd_count <= 1)
		return (0);
	*pipe_fds = malloc((cmd_count - 1) * 2 * sizeof(int));
	if (!*pipe_fds)
		return (-1);
	while (i < cmd_count - 1)
	{
		if (pipe(*pipe_fds + i * 2) == -1)
			return (-1);
		i++;
	}
	return (0);
}

/*
Manages stdin/stdout redirection for a child process
*/
void	setup_child_fds(int i, int *pipe_fds, int cmd_count)
{
	if (i > 0)
	{
		if (dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO) == -1)
			sys_error("dup2", ERR_DUP2);
	}
	if (i < cmd_count - 1)
	{
		if (dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO) == -1)
			sys_error("dup2", ERR_DUP2);
	}
}
