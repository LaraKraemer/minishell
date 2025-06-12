/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:15:00 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:47 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_data(t_data *data)
{
	if (data->pipe_fd)
		free(data->pipe_fd);
	if (data->child_pid)
		free(data->child_pid);
	if (data->command.cmd_path)
		free(data->command.cmd_path);
	if (data->command.cmd_argv)
		free_array(data->command.cmd_argv);
	if (data->path_file)
		free_array(data->path_file);
}

void	free_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		free (str_array[i++]);
	free (str_array);
}
	*/
