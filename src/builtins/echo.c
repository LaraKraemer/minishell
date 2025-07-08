/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:53:19 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/08 21:03:08 by lkramer          ###   ########.fr       */
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
int	echo_builtin(t_command *cmd, char **env)
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
		if (cmd->cmd_args[i][1] == '?')
			echo_exit_code(cmd->cmd_args[i]);
		if (cmd->cmd_args[i][0] == '$')
			echo_env(cmd->cmd_args[i], env);
		else
			printf("%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
    fflush(stdout);
    if (cmd->fd_out != STDOUT_FILENO)
        close(cmd->fd_out);
	return (0);
}

/*
Calls env function and prints respective value to STDOUT
*/
void echo_env(char *arg, char **env)
{
    char *expanded_var;

    if (!arg || !env)
        return;
    if (arg[0] == '$')
        arg++;
    expanded_var = get_env_value(arg, env);
    if (expanded_var)
        printf("%s", expanded_var);
}

/*
Calls exit function and prints respective value to STDOUT
*/
void echo_exit_code(char *arg)
{
	char	*expanded_exit;

	if (!arg)
        return;
    if (arg[0] == '$')
        arg++;
	expanded_exit = expand_exit_code(arg);
	if (expanded_exit)
		printf("%s", expanded_exit);
}