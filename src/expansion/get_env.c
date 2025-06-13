/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:16:31 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/13 17:01:25 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Retrieves value of an environment variable.

Returns a pointer to variable's value after '=' 
or NULL if variable doesn't exist.
*/
char	*get_env_value(char *arg, char **env)
{
	size_t	arg_len;
	int		i;

	if (!arg || !env)
		return (NULL);
	i = 0;
	arg_len = ft_strlen(arg);
	while(env[i])
	{
		if (ft_strncmp(env[i], arg, arg_len) == 0 && env[i][arg_len] == '=')
			return (env[i] + arg_len + 1);
		i++;
	}
	return (NULL);
}

/*
char *expand_var(char *arg, char **env)
{
	char	*value;
	char	*result;
	int		exit_code;

	if (ft_strcmp(arg[0], '?') == 0)
		value = ft_itoa(exit_code);
	else
		value = get_env_value(arg, env);
	if (value != NULL)
	{
		result = ft_strdup(value);
		if (ft_strcmp(arg, '?') == 0)
			free(value);
		return (result);
	}
	else
		return (ft_strdup(""));
}

*/
/*


char *get_env_value(char *name, char **env)
{
	
}

int get_exit_status(char *exit_status)
{
	
}
*/
