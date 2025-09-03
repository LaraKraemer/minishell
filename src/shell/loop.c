/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:59:09 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/02 18:30:15 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	minishell_loop(t_shell *sh, char ***global_env)
{
	if (isatty(STDIN_FILENO))
		print_banner();
	while (1)
	{
		sh->error_in_setup = 0;
		if (!read_trim_input(sh))
		{
			if (!isatty(STDIN_FILENO))
				break ;
			continue ;
		}
		if (!tokenize_input(sh, *global_env))
			continue ;
		if (!parse_prepare_cmds(sh, *global_env))
			continue ;
		if (!setup_paths(sh, *global_env))
		{
			free_resources(sh->input, sh->cmds_array, sh->cmd_count);
			continue ;
		}
		if (handle_builtins(sh, global_env))
			continue ;
		execute_commands(sh);
	}
}
