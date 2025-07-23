/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:23:54 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/23 18:46:18 by lkramer          ###   ########.fr       */
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
	free_env(global_env);
	return (0);
}

/* 
Processes export arguments to add or update environment variables.
*/
int	update_add_var(char **args, char ***global_env)
{
	int		i;
	char	*equal_sign;
	char    **new_env;

	i = 1;
	new_env = NULL;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			ft_putstr_fd(ERR_ENV, 2);
			i++;
			continue;
		}
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			new_env = assign_var_and_value(equal_sign, args[i],*global_env);
		else
			new_env = assign_var(args[i], *global_env);
		if (!new_env)
			return (1);
		*global_env = new_env;
		i++;
	}
	return (0);
}

/* 
Creates a new environment array with an additional variable.
*/
char **add_new_env_var(char *var, char ***env)
{
    int     count;
    char    **new_env;
    char    *new_var;

    count = 0;
    while ((*env)[count])
        count++;
    new_env = ft_calloc(count + 2, sizeof(char *));
    if (!new_env)
        return (NULL);
    ft_memcpy(new_env, *env, count * sizeof(char *));
    new_var = ft_strdup(var);
    if (!new_var)
    {
        free(new_env);
        return (NULL);
    }
    new_env[count] = new_var;
    new_env[count + 1] = NULL;
    free(*env);
    return (new_env);
}

/* 
Handles VAR=value assignments by updating or adding variables
*/
char **assign_var_and_value(char *equal_sign, char *arg, char **env)
{
    int     j;
    size_t  var_len;
    char    *var;

    j = 0;
    var_len = equal_sign - arg;
    var = ft_substr(arg, 0, var_len);
    if (!var)
        return (NULL);
    while (env[j])
    {
        if ((ft_strncmp(env[j], var, var_len) == 0 && 
            (env[j][var_len] == '=' || env[j][var_len] == '\0')))
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
char **assign_var(char *arg, char **env)
{
    int     j;
    size_t  var_len;

    j = 0;
    var_len = ft_strlen(arg);
    while (env[j])
    {
        if ((ft_strncmp(env[j], arg, var_len) == 0 && 
            (env[j][var_len] == '=' || env[j][var_len] == '\0')))
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