/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:25:28 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 18:00:28 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/*Initializes an array of command structures.*/
int	init_array(t_command *cmds_array, int cmd_count, char **envp)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		cmds_array[i].cmd = NULL;
		cmds_array[i].cmd_args = NULL;
		cmds_array[i].env = copy_env(envp);
		if (!cmds_array[i].env)
			return (error_input(ERR_MEM_ALLO, 0));
		cmds_array[i].fd_in = STDIN_FILENO;
		cmds_array[i].fd_out = STDOUT_FILENO;
		cmds_array[i].path_file = NULL;
		cmds_array[i].cmd_path = NULL;
		cmds_array[i].exit_code = 0;
		cmds_array[i].redir_err_flag = 0;
		i++;
	}
	cmds_array[i].cmd = NULL;
	return (1);
}
