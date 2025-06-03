/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:23:54 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/03 18:35:44 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/execution.h"

/*
export (with no options)
export VAR ☑️
export VAR=value

Return error:
export 1VAR=value	
*/
int export_builtin(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}