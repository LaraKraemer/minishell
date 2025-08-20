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
int	echo_builtin(t_command *cmd)
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
		printf("%s", cmd->cmd_args[i]);
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
