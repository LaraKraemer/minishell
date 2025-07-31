/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:53:30 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 12:56:12 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	init_shell(t_shell *sh)
{
    sh->input = NULL;
    sh->raw_input = NULL;
    sh->first_token = NULL;
    sh->cmd_count = 0;
    sh->cmds_array = NULL;
    sh->exit_code = 0;
    sh->error_in_setup = 0;
    sh->i = 0;
}

int	read_trim_input(t_shell *sh)
{
    sh->raw_input = readline("minishell🐣>$ ");
    if (!sh->raw_input)
        return (0);
    sh->input = ft_strtrim(sh->raw_input, " \t\n");
    free(sh->raw_input);
    if (!sh->input || !*sh->input)
    {
        free(sh->input);
        return (0);
    }
    add_history(sh->input);
    return (1);
}