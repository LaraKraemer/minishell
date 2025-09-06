/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_tokenizer_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:55:53 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/05 16:55:51 by 123              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	tokenize_input(t_shell *sh, char **global_env)
{
	sh->first_token = NULL;
	if (get_tokens(sh->input, &sh->first_token, global_env, sh->exit_code))
		return (0);
	return (1);
}

int	parse_prepare_cmds(t_shell *sh, char **global_env)
{
	sh->cmd_count = count_cmd_num(sh->first_token);
	sh->cmds_array = malloc((sh->cmd_count + 1) * sizeof(t_command));
	if (!sh->cmds_array)
	{
		free_if_error(sh->input, &sh->first_token);
		return (error_input(ERR_MEM_ALLO, 1));
	}
	if (!parse_input
		(sh->cmds_array, sh->first_token, sh->cmd_count,
			sh->exit_code, global_env))
	{
		if (!sh->cmds_array->exit_code)
			sh->exit_code = 258;
		else
			sh->exit_code = sh->cmds_array->exit_code;
		free_if_error(sh->input, &sh->first_token);
		free(sh->cmds_array);
		return (0);
	}
	return (1);
}
