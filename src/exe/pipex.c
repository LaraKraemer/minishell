/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:02:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:12 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
static void	init_data(t_data *data, int argc)
{
	data->command.cmd_count = argc - 3;
	data->command.cmd_argv = NULL;
	data->command.cmd_path = NULL;
	data->fd_in = -1;
	data->fd_out = -1;
	data->path_file = NULL;
	data->child_pid = malloc(data->command.cmd_count * sizeof(pid_t));
	if (data->child_pid == NULL)
	{
		ft_putendl_fd("Malloc failed", 2);
		exit(1);
	}
	data->pipe_fd = malloc((data->command.cmd_count - 1) * 2 * sizeof(int));
	if (data->pipe_fd == NULL)
	{
		ft_putendl_fd("Malloc failed", 2);
		if (data->child_pid)
			free(data->child_pid);
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	if (argc != 5)
	{
		ft_putendl_fd("Wrong number of arguments", 2);
		return (0);
	}
	init_data(&data, argc);
	if (set_path(&data, envp) == -1)
	{
		free_data(&data);
		return (0);
	}
	interprocess_communication(&data, argv, envp);
	free_data(&data);
}
*/
