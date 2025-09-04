/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:53:19 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/02 18:42:06 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

static int	parse_echo_args(char **args, int *start_index)
{
	*start_index = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		*start_index = 2;
		return (0);
	}
	return (1);
}

static void	print_args(char **args, int start_index, int fd)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
}

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
	int	start_index;
	int	new_line;

	if (!cmd || !cmd->cmd_args)
		return (0);
	new_line = parse_echo_args(cmd->cmd_args, &start_index);
	print_args(cmd->cmd_args, start_index, STDOUT_FILENO);
	if (new_line)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
