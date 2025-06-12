/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:56:27 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/03 15:17:38 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/*
static int	err_handl(char *fname, char *msg, int error)
{
	ft_putstr_fd(fname, 2);
	ft_putendl_fd(msg, 2);
	return (error);
}

static char	*extract_command(t_data *data, char *command)
{
	data->command.cmd_argv = ft_split(command, ' ');
	if (data->command.cmd_argv == NULL)
	{
		ft_putendl_fd("Malloc failed", 2);
		return (NULL);
	}
	return (data->command.cmd_argv[0]);
}

static int	find_path(t_data *data, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (data->path_file[i])
	{
		temp = ft_strjoin(data->path_file[i], cmd);
		if (temp == NULL)
			return (err_handl(cmd, ": command not found", 127));
		if (access(temp, F_OK) == 0)
		{
			data->command.cmd_path = temp;
			return (0);
		}
		free(temp);
		i++;
	}
	return (err_handl(cmd, ": command not found", 127));
}

int	check_command(t_data *data, char *command)
{
	char	*cmd;
	int		error;

	cmd = extract_command(data, command);
	if (cmd == NULL)
		return (-1);
	error = 0;
	if (ft_strchr(command, '/') == NULL)
		error = find_path(data, cmd);
	else if (access(command, F_OK))
		return (err_handl(cmd, ": command not found", 127));
	else
		data->command.cmd_path = command;
	if (error)
		return (error);
	if (access(data->command.cmd_path, X_OK) != 0)
		return (err_handl(cmd, ": is not executable", 126));
	return (0);
}

int	open_file(t_data *data, char *file, int i)
{
	if (i == 0)
	{
		data->fd_in = open(file, O_RDONLY);
		if (data->fd_in == -1)
		{
			perror("Error with opening file");
			return (-1);
		}
	}
	else if (i == data->command.cmd_count - 1)
	{
		data->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->fd_out == -1)
		{
			perror("Error with opening file");
			return (-1);
		}
	}
	return (0);
}

*/
