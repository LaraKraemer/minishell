/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:23:54 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 14:26:08 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/*
Runs in parent process - since it affects env of shell

export
export VAR=value
export VAR

Return error:
export 1VAR=value	
*/

int	export_builtin(t_command *cmd, char ***global_env)
{
	if (!cmd->cmd_args[1])
		return (export_without_var(*global_env));
	else
		return (update_add_var(cmd->cmd_args, global_env));
	return (0);
}

/* 
Handles export without arguments by printing sorted environment variables.
*/
int	export_without_var(char **global_env)
{
	sort_env(global_env);
	print_export(global_env);
	return (0);
}

/* 
Processes export arguments to add or update environment variables.
*/
int	update_add_var(char **args, char ***global_env)
{
	int		i;
	char	*equal_sign;
	int		exit_code;

	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			print_error(args[i], ERR_ENV);
			exit_code = 1;
			i++;
			continue ;
		}
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			*global_env = assign_var_and_value(equal_sign, args[i],*global_env);
		else
			*global_env = assign_var(args[i], *global_env);
		if (!*global_env)
			return (1);
		i++;
	}
	return (exit_code);
}

/* 
Handles VAR=value assignments by updating or adding variables
*/
char	**assign_var_and_value(char *equal_sign, char *arg, char **env)
{
	int		j;
	size_t	var_len;
	char	*var;

	j = 0;
	var_len = equal_sign - arg;
	var = ft_substr(arg, 0, var_len);
	if (!var)
		return (NULL);
	while (env[j])
	{
		if ((ft_strncmp(env[j], var, var_len) == 0
				&& (env[j][var_len] == '=' || env[j][var_len] == '\0')))
		{
			free(env[j]);
			env[j] = ft_strdup(arg);
			free(var);
			return (env);
		}
		j++;
	}
	free(var);
	return (add_new_env_var(arg, &env));
}

/* 
Handles bare variable names (without values) in export statements
*/
char	**assign_var(char *arg, char **env)
{
	int		j;
	size_t	var_len;

	j = 0;
	var_len = ft_strlen(arg);
	while (env[j])
	{
		if ((ft_strncmp(env[j], arg, var_len) == 0
				&& (env[j][var_len] == '=' || env[j][var_len] == '\0')))
		{
			return (env);
		}
		j++;
	}
	return (add_new_env_var(arg, &env));
}

/* void print_env(char **env)
{
    int i = 0;
    while (env[i])
    {
        printf("env[%d]: %s\n", i, env[i]);
        i++;
    }
} */