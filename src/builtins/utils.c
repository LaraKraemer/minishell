/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:03:18 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/03 14:15:50 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

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
int	builtins(t_command *cmd, char **env)
{
	char	cwd[BUFSIZ];

	if (!cmd || !cmd->cmd_args[0])
        return (0);
	const char *cmd_name = cmd->cmd_args[0];
		
	if (ft_strcmp(cmd_name, "cd") == 0)
		cd_builtin(cmd, env);
	else if (ft_strcmp(cmd_name, "echo") == 0)
		echo_builtin(cmd, env);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		pwd_builtin(cmd->cmd_args, cwd, sizeof(cwd));
	else if (ft_strcmp(cmd_name, "export") == 0)
		export_builtin(cmd->cmd_args, env);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		unset_builtin(cmd->cmd_args, env);
	else if (ft_strcmp(cmd_name, "env") == 0)
		env_builtin(env);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		exit_builtin(cmd->cmd_args);
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
