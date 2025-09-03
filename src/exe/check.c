/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:56:27 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/02 18:41:01 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"
#include <fcntl.h>

#ifndef O_DIRECTORY
#define O_DIRECTORY 0200000
#endif

/*
	Debug Messages:
	printf("Searching PATH directories:\n");
	printf("cmd: %s\n", cmd->cmd);
	printf("cmd_path: %s\n", cmd->cmd_path);
	printf("  FOUND at: %s\n", temp);
	printf("Calling find path\n");
*/
static int	find_path(t_command *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (!cmd->path_file)
		return (print_error(cmd->cmd, ERR_PATH), 127);
	while (cmd->path_file && cmd->path_file[i])
	{
		temp = ft_strjoin(cmd->path_file[i], cmd->cmd);
		if (!temp)
			return (print_error(cmd->cmd, ERR_MEM_ALLO), 127);
		if (temp == NULL)
			return (print_error(cmd->cmd, ERR_CMD_NFOUND), 127);
		if (access(temp, F_OK) == 0)
		{
			cmd->cmd_path = temp;
			return (0);
		}
		free(temp);
		i++;
	}
	return (print_error(cmd->cmd, ERR_CMD_NFOUND), 127);
}

int	handle_absolute_path(t_command *cmd)
{
	int 	dir_fd;

	if (access(cmd->cmd, F_OK) != 0)
	{
		cmd->exit_code = 127;
		return (print_error(cmd->cmd, EER_NO_FILE), 127);
	}
	dir_fd = open(cmd->cmd, O_DIRECTORY);
	if (dir_fd != -1)
    {
        close(dir_fd);
        cmd->exit_code = 126;
        return (print_error(cmd->cmd, ERR_IS_DIR), 126);
    }
	cmd->cmd_path = ft_strdup(cmd->cmd);
	if (!cmd->cmd_path)
	{
		cmd->exit_code = 127;
		return (print_error(cmd->cmd, ERR_MEM_ALLO), 127);
	}
	return (0);
}

int	handle_relative_path(t_command *cmd)
{
	int	error;

	error = find_path(cmd);
	if (error)
	{
		cmd->exit_code = 127;
		return (error);
	}
	return (0);
}

int	check_command(t_command *cmd)
{
	int	error;

	error = 0;
	if (ft_strchr(cmd->cmd, '/') != NULL)
		error = handle_absolute_path(cmd);
	else
		error = handle_relative_path(cmd);
	if (error)
		return (error);
	if (access(cmd->cmd_path, X_OK) != 0)
	{
		cmd->exit_code = 126;
		return (print_error(cmd->cmd, ERR_PERMISSION), 126);
	}
	cmd->exit_code = 0;
	return (0);
}
