/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:05:39 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 14:11:01 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/* 
Creates a new environment array with an additional variable.
*/
char	**add_new_env_var(char *var, char ***env)
{
	int		count;
	char	**new_env;
	char	*new_var;

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
