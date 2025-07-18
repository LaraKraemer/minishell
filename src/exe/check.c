/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:56:27 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/04 17:11:17 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

static int	err_handl(char *fname, char *msg, int error)
{
	ft_putstr_fd(fname, 2);
	ft_putendl_fd(msg, 2);
	return (error);
}

/* printf("Searching PATH directories:\n");
	printf("cmd: %s\n", cmd->cmd);
	printf("cmd_path: %s\n", cmd->cmd_path); */
	
static int	find_path(t_command *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (!cmd->path_file)
    	return (err_handl(cmd->cmd, ": PATH not set", 127));
	while (cmd->path_file && cmd->path_file[i])
	{
		temp = ft_strjoin(cmd->path_file[i],cmd->cmd);
		if (!temp)
            return (err_handl(cmd->cmd, ": allocation failed", 127));
		if (temp == NULL)
			return (err_handl(cmd->cmd, ": command not found", 127));
		if (access(temp, F_OK) == 0)
		{
			printf("  FOUND at: %s\n", temp);
			cmd->cmd_path = temp;
			return (0);
		}
		free(temp);
		i++;
	}
	return (err_handl(cmd->cmd, ": command not found", 127));
}

int	check_command(t_command *cmd)
{
	int		error;

	error = 0;
	if (ft_strchr(cmd->cmd, '/') != NULL)
	{
		if (access(cmd->cmd, F_OK) != 0)
			return (err_handl(cmd->cmd, ": no such file", 127));
		cmd->cmd_path = ft_strdup(cmd->cmd);
		if (!cmd->cmd_path)
            return (err_handl(cmd->cmd, ": allocation failed", 127));
	}
	else
	{
		printf("Calling find path\n");
		error = find_path(cmd);
		if (error)
			return (error);
	}
	if (access(cmd->cmd_path, X_OK) != 0)
		return (err_handl(cmd->cmd, ": permission denied", 126));
	return (0);
}
