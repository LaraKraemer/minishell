/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:52:03 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/08 21:15:05 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"


static int	extract_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	ft_putendl_fd("Failed to find the PATH", 2);
	return (-1);
}

static int	add_slash_topath(char ***dest, char **path_file)
{
	int	i;

	i = 0;
	while (path_file[i])
		i++;
	*dest = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (path_file[i])
	{
		(*dest)[i] = ft_strjoin(path_file[i], "/");
		if (!(*dest)[i])
		{
			free_array(path_file);
			free_array(*dest);
			return (-1);
		}
		i++;
	}
	(*dest)[i] = NULL;
	free_array(path_file);
	return (0);
}

int	set_path(t_command *cmd, char *envp[])
{
	char	*path;
	char	**split_path;
	char	**path_cache;
	int		i;

	if (cmd->path_file)
        free_array(cmd->path_file);
	path_cache = NULL;
	if (path_cache == NULL) {
        i = extract_path(envp);
        if (i == -1) 
			return (-1);
        path = ft_strtrim(envp[i], "PATH=");
        split_path = ft_split(path, ':');
        free(path);
		// Debug: Print each path in the split PATH
        /* for (int j = 0; split_path[j]; j++) {
            printf("\033[0;31mDebug: split_path[%d] = %s\033[0m\n", j, split_path[j]);
        } */
        if (add_slash_topath(&path_cache, split_path) == -1)
            return (-1);
    }
    cmd->path_file = path_cache;
    return (0);
}

