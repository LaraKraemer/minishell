/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:15:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/12 20:18:21 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Filter function for builtin cmd in parent process
*/
int must_run_in_parent(const char *cmd)
{
	int i;
    const char *parent_builtins[6] = {"cd", "export", "unset", "exit", NULL};

	i = 0;
    while (parent_builtins[i])
	{
        if (ft_strcmp(cmd, parent_builtins[i]) == 0)
            return 1;
		i++;
	}
    return 0;
}

void	free_commands(t_command *cmds, int cmd_count)
{
	int i = 0;

	while (i < cmd_count)
	{
		if (cmds[i].cmd_path)
			free(cmds[i].cmd_path);
		if (cmds[i].cmd_args)
			free_array(cmds[i].cmd_args);
		if (cmds[i].env)
			free_array(cmds[i].env);
		if (cmds[i].path_file)
			free_array(cmds[i].path_file);
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
void	create_pipe(t_data *data, int i)
{
	if (pipe(&data->pipe_fd[2 * i]) == -1)
	{
		perror("Pipe failed");
		free_data(data);
		exit(1);
	}
}

void	cleanup_and_exit(t_data *data, int i, int err)
{
	close_fds(data, i);
	free_data(data);
	exit(err);
}

void	close_fds(t_data *data, int i)
{
	if (i == 0)
	{
		close(data->pipe_fd[2 * i]);
		if (data->fd_in != -1)
			close(data->fd_in);
		close(data->pipe_fd[2 * i + 1]);
	}
	else if (i == data->command.cmd_count - 1)
	{
		close(data->pipe_fd[2 * i - 2]);
		close(data->pipe_fd[2 * i - 1]);
		if (data->fd_out != -1)
			close(data->fd_out);
	}
	else
	{
		close(data->pipe_fd[2 * i - 2]);
		close(data->pipe_fd[2 * i - 1]);
		close(data->pipe_fd[2 * i]);
		close(data->pipe_fd[2 * i + 1]);
	}
}
	*/
