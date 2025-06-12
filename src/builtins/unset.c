/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:44:54 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/12 13:55:58 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Runs in parent process - since it affects env of shell
*/
int	unset_builtin(char **args, char **env)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			ft_putstr_fd(ERR_ENV, 2);
			i++;
			continue ;
		}
		remove_var_from_env(args[i], env);
		i++;
	}
	return (0);
}

void	remove_var_from_env(char *args, char **env)
{
	int	i;
	int	arg_len;

	i = 0;
	arg_len = ft_strlen(args);
	while (env[i])
	{
		if (ft_strncmp(env[i], args, arg_len) == 0 && (env[i][arg_len] == '='
			|| env[i][arg_len] == '\0'))
		{
			free(env[i]);
			while (env[i + 1])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			break ;
		}
		i++;
	}
}
