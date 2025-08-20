/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:53:19 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 17:28:47 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/*
Runs in child process - no issues with forking since 
it doesn’t change anything.

echo hello world
Output: hello world\n

echo -n hello
Output: hello (No Trailing newline)

No errors - always returns 0
*/
int	echo_builtin(t_command *cmd, char **env, int exit_code)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	if (!cmd || !cmd->cmd_args)
		return (0);
	if (cmd->cmd_args[i] && ft_strcmp(cmd->cmd_args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		check_echo_arg(cmd->cmd_args[i], env, exit_code);
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

void	check_echo_arg(char *arg, char **env, int exit_code)
{
	if (arg[1] == '?')
		echo_exit_code(arg, exit_code);
	else if (arg[0] == '$' && arg[1] != '\0')
		echo_env(arg, env);
	else
		printf("%s", arg);
}

/*
Calls env function and prints respective value to STDOUT
*/
void	echo_env(char *arg, char **env)
{
	char	*expanded_var;

	if (!arg || !env)
		return ;
	if (arg[0] == '$')
		arg++;
	expanded_var = get_env_value(arg, env);
	if (expanded_var)
		printf("%s", expanded_var);
}

/*
Calls exit function and prints respective value to STDOUT
*/
void	echo_exit_code(char *arg, int exit_code)
{
	char	*expanded_exit;

	expanded_exit = expand_exit_code(arg, exit_code);
	if (expanded_exit)
		printf("%s", expanded_exit);
	free(expanded_exit);
}
