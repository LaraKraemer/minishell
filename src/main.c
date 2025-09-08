/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:23 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/06 11:26:38 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;
	char		**global_env;
	int			final_exit_code;

	(void)argc;
	(void)argv;
	init_shell(&sh);
	setup_interactive_sigs();
	global_env = copy_env(envp);
	if (!global_env)
		return (error_input("malloc", 0));
	sh.global_env = global_env;
	minishell_loop(&sh, &global_env);
	final_exit_code = sh.exit_code;
	free_array(global_env);
	return (final_exit_code);
}
