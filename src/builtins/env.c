/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:39:29 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/22 16:50:29 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/*
Runs in child process - no issues with forking since 
it doesn’t change anything.

Returns global env variables

Returns always 0
*/
int	env_builtin(char **env)
{
	int	i;

	if (!env)
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd("environment not found\n", STDERR_FILENO);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
