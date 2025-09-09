/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_builtin_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:57:44 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/09 13:15:44 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*
Sets up executable paths for non-builtin commands in the command array.
Skips builtin commands as they don't require path resolution.
*/
int	setup_paths(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->cmd_count)
	{
		if (sh->cmds_array[i].cmd_args && sh->cmds_array[i].cmd_args[0]
			&& is_builtin(sh->cmds_array[i].cmd_args[0]))
		{
			i++;
			continue ;
		}
		if (set_path(&sh->cmds_array[i], sh->global_env) == -1)
		{
			sh->exit_code = error_input(ERR_PATH, 127);
			sh->error_in_setup = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

/*
Handles execution of builtin commands with redirection support.
Executes builtin commands directly in parent process.
Saves and restores original stdout to ensure shell state remains intact.
*/
int	handle_builtins(t_shell *sh)
{
	if (sh->cmd_count == 1 && sh->cmds_array[0].cmd_args
		&& must_run_in_parent(sh->cmds_array[0].cmd_args[0]))
	{
		if (sh->cmds_array->fd_in == -1 || sh->cmds_array->fd_out == -1)
		{
			free_resources(sh->input, sh->cmds_array, sh->cmd_count,
				&sh->first_token);
			sh->exit_code = 1;
			return (1);
		}
		sh->exit_code = builtins(&sh->cmds_array[0], sh);
		free_resources(sh->input, sh->cmds_array, sh->cmd_count,
			&sh->first_token);
		return (1);
	}
	return (0);
}

void	execute_commands(t_shell *sh)
{
	sh->exit_code = execute_with_pipex_logic(sh);
	free_resources(sh->input, sh->cmds_array, sh->cmd_count, &sh->first_token);
}
