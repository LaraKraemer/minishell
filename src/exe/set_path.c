/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:52:03 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:36 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
static int	extract_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
	{
		ft_putendl_fd("Failed to find the path", 2);
		return (-1);
	}
	return (i);
}

static int	add_slash_topath(t_data *data, char **path_file)
{
	int	i;

	i = 0;
	while (path_file[i])
		i++;
	data->path_file = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (path_file[i])
	{
		data->path_file[i] = ft_strjoin(path_file[i], "/");
		if (data->path_file == NULL)
		{
			free_array(path_file);
			free_array(data->path_file);
			return (-1);
		}
		i++;
	}
	data->path_file[i] = NULL;
	free_array(path_file);
	return (0);
}

int	set_path(t_data *data, char *envp[])
{
	char	*path;
	char	**path_file;
	int		i;

	i = extract_path(envp);
	if (i == -1)
		return (-1);
	path = ft_strtrim(envp[i], "PATH=");
	if (path == NULL || ft_strlen(path) == 0)
	{
		ft_putendl_fd("Failed to find the path", 2);
		return (-1);
	}
	path_file = ft_split(path, ':');
	free(path);
	if (path_file == NULL || add_slash_topath(data, path_file) == -1)
	{
		ft_putendl_fd("Failed to find the path", 2);
		return (-1);
	}
	return (0);
}

*/
