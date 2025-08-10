/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_builtin_exe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:57:44 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 13:53:01 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	setup_paths(t_shell *sh, char **global_env)
{
	int	i;

	i = 0;
	while (i < sh->cmd_count)
	{
		if (set_path(&sh->cmds_array[i], global_env) == -1)
		{
			error_input(ERR_PATH, 127);
			sh->exit_code = 127;
			sh->error_in_setup = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	handle_builtins(t_shell *sh, char ***global_env)
{
	if (sh->cmd_count == 1 && is_builtin(sh->cmds_array[0].cmd_args[0]))
	{
		sh->exit_code = builtins(&sh->cmds_array[0], global_env);
		free_resources(sh->input, sh->cmds_array, sh->cmd_count);
		return (1);
	}
	return (0);
}

void	execute_commands(t_shell *sh)
{
	sh->exit_code = execute_with_pipex_logic(sh->cmds_array, sh->cmd_count);
	free_resources(sh->input, sh->cmds_array, sh->cmd_count);
}
