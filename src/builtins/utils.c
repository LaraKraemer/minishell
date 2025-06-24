/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:03:18 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/16 16:43:34 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Identifies builtin commands from input.

Returns 0 on success 
Returns 1 on failure 
*/
int	is_builtin(char *arg)
{
	int		i;
	char	*builtin_list[8];

	builtin_list[0] = "cd";
	builtin_list[1] = "echo";
	builtin_list[2] = "pwd";
	builtin_list[3] = "export";
	builtin_list[4] = "unset";
	builtin_list[5] = "env";
	builtin_list[6] = "exit";
	builtin_list[7] = NULL;
	i = 0;
	while (builtin_list[i])
	{
		if (ft_strcmp(arg, builtin_list[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
Verifies and calls builtin cmd function.

Returns 0 on success 
Returns 1 on failure 
*/
int	builtins(char **args, char **env)
{
	char	cwd[BUFSIZ];

	if (args[0] == NULL)
   		return (0);
	if (ft_strcmp(args[0], "cd") == 0)
		cd_builtin(args[1], env);
	else if (ft_strcmp(args[0], "echo") == 0)
		echo_builtin(args, env);
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

/*
Function verifies whether two strings are identical.

Returns 0 on success 
Returns 1 on failure 
*/
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
