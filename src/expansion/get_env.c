/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:16:31 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 14:29:31 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"

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
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, arg_len) == 0 && env[i][arg_len] == '=')
			return (ft_strdup(env[i] + arg_len + 1));
		i++;
	}
	return (ft_strdup(""));
}
