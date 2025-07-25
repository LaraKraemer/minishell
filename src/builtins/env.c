/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:39:29 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/24 14:04:05 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/*
Runs in child process - no issues with forking since 
it doesn’t change anything.

Returns global env variables

Returns always 0
*/
int	env_builtin(char **args, char **env)
{
	int	i;

	i = 0;
	if (args[1])
		return (print_error(args[1], EER_NO_FILE), 127);
    if (!env || !env[0])
        return (print_error(args[1], EER_ENV_NFOUND), 1);
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
