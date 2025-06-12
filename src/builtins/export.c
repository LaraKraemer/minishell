/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:23:54 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/12 13:55:44 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Runs in parent process - since it affects env of shell

export (with no options)
export VAR ☑️
export VAR=value
export VAR

Return error:
export 1VAR=value	
*/

int	export_builtin(char **args, char **env)
{
	if (!args[1])
		return (export_without_var(env));
	else
		return (update_add_var(args, env));
	return (0);
}

int	export_without_var(char **env)
{
	char	**dup_env;

	dup_env = copy_env(env);
	if (!dup_env)
		return (1);
	sort_env(dup_env);
	print_export(dup_env);
	free_env(dup_env);
	return (0);
}

int	update_add_var(char **args, char **env)
{
	int		i;
	char	*equal_sign;

	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			ft_putstr_fd(ERR_ENV, 2);
			i++;
			continue ;
		}
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			assign_var_and_value(equal_sign, env, args[i]);
		else
			assign_var(env, args[i]);
		i++;
	}
	return (0);
}

char	**assign_var_and_value(char *equal_sign, char **env, char *args)
{
	int		j;
	size_t	var_len;
	char	*var;

	j = 0;
	var_len = equal_sign - args;
	var = ft_substr(args, 0, var_len);
	while (env[j])
	{
		if ((ft_strncmp(env[j], var, var_len) == 0 && env[j][var_len] == '='))
		{
			free_env(&env[j]);
			env[j] = ft_strdup(args);
			free(var);
			return (env);
		}
		j++;
	}
	env[j] = ft_strdup(args);
	env[j + 1] = NULL;
	free(var);
	return (env);
}

char	**assign_var(char **env, char *args)
{
	int		j;
	size_t	var_len;
	char	*new_var;

	j = 0;
	var_len = ft_strlen(args);
	while (env[j])
	{
		if ((ft_strncmp(env[j], args, var_len) == 0 && env[j][var_len] == '=')
		|| env[j][var_len] == '\0')
			return (env);
		j++;
	}
	new_var = ft_strjoin(args, "=");
	env[j] = new_var;
	env[j + 1] = NULL;
	return (env);
}
