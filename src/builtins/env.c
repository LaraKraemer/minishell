/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:39:29 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/03 18:05:45 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/execution.h"

int env_builtin(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
