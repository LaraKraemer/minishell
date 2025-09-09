/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-08 13:42:50 by dtimofee          #+#    #+#             */
/*   Updated: 2025-09-08 13:42:50 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

int	is_redirection_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC);
}

void	free_and_exit(t_shell *sh, char *temp, char *delimiter)
{
	free_resources(sh->input, sh->cmds_array, sh->cmd_count,
		&sh->first_token);
	free_array(sh->global_env);
	free(temp);
	free(delimiter);
	exit(0);
}
