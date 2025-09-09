/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:59:09 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/08 15:44:32 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	minishell_loop(t_shell *sh)
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
		if (!tokenize_input(sh))
			continue ;
		if (!parse_prepare_cmds(sh))
			continue ;
		if (!setup_paths(sh))
		{
			free_resources(sh->input, sh->cmds_array, sh->cmd_count,
				&sh->first_token);
			continue ;
		}
		if (handle_builtins(sh))
			continue ;
		execute_commands(sh);
	}
}
