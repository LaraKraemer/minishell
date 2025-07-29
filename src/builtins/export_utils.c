/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:27:35 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/24 15:06:53 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

char	**copy_env(char **env)
{
	int		i;
	int		j;
	char	**env_dup;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	env_dup = malloc((i + 1) * sizeof(char *));
	if (!env_dup)
		return (print_error("malloc", ERR_MEM_ALLO), NULL);
	while (j < i)
	{
		env_dup[j] = ft_strdup(env[j]);
		j++;
	}
	env_dup[i] = NULL;
	return (env_dup);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp_env;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp_env = env[i];
				env[i] = env[j];
				env[j] = temp_env;
			}
			j++;
		}
		i++;
	}
}

int	valid_identifier(char *arg)
{
	int	i;

	i = 0;
	// printf("%c\n", arg[0]);
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("declare -x %s\n", env[i]);
		i++;
	}
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
