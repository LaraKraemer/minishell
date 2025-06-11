/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:03:18 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/11 13:47:17 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

int	builtins(char **args, char **env)
{
	char	cwd[BUFSIZ];

	if (args[0] == NULL)
   		return (0);
	if (ft_strcmp(args[0], "cd") == 0)
		cd_builtin(args[1]);
	else if (ft_strcmp(args[0], "echo") == 0)
		echo_builtin(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd_builtin(args, cwd, sizeof(cwd));
	else if (ft_strcmp(args[0], "export") == 0)
		export_builtin(args, env);
	else if (ft_strcmp(args[0], "unset") == 0)
		unset_builtin(args, env);
	else if (ft_strcmp(args[0], "env") == 0)
		env_builtin(env);
	else if (ft_strcmp(args[0], "exit") == 0)
		exit_builtin(args);
	return (EXIT_SUCCESS);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t					i;
	const unsigned char		*src1;
	const unsigned char		*src2;

	i = 0;
	src1 = (const unsigned char *) s1;
	src2 = (const unsigned char *) s2;
	while (src1[i] || src2[i])
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}
