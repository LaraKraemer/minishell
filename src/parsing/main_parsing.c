/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:59:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/07 14:25:24 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/*Iterates through the token list and counts
the number of commands based on PIPE tokens.*/
int	count_cmd_num(t_token *first_token)
{
	t_token	*current;
	int		pipe_count;

	current = first_token;
	pipe_count = 0;
	while (current->next)
	{
		if (current->type == TOKEN_PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count + 1);
}

static void	handle_words(t_token **start, t_shell *sh,
		t_command *cmd, int *i)
{
	if (!cmd->cmd)
		cmd->cmd = quotes_token((*start)->value, sh->global_env,
				sh->exit_code);
	cmd->cmd_args[(*i)++] = quotes_token((*start)->value, sh->global_env,
			sh->exit_code);
}

int	fill_cmd_struct(t_token **start, t_shell *sh, t_command *cmd)
{
	int	return_from_redirections;
	int	i;

	i = 0;
	while (*start && (*start)->type != TOKEN_PIPE)
	{
		if (is_redirection_token(*start))
		{
			return_from_redirections = handle_redirections(cmd, start, sh);
			if (return_from_redirections == 0)
				return (0);
			else if (return_from_redirections == -1)
				continue ;
		}
		else if ((*start)->type == TOKEN_WORD)
			handle_words(start, sh, cmd, &i);
		*start = (*start)->next;
	}
	cmd->cmd_args[i] = NULL;
	return (1);
}

/*Processes the token list and extracts information for a single command
 (command name, arguments, redirections). Updates the command structure
 and moves the token pointer to the next command.*/
int	split_into_cmds(t_command *cmd, t_shell *sh)
{
	t_token	*start;

	start = sh->first_token;
	cmd->cmd_args = malloc(MAX_ARGS * sizeof(char *));
	if (!cmd->cmd_args)
		return (error_input(ERR_MEM_ALLO, 0));
	ft_bzero(cmd->cmd_args, MAX_ARGS * sizeof(char *));
	if (!fill_cmd_struct(&start, sh, cmd))
		return (0);
	if (start)
		start = start->next;
	sh->first_token = start;
	return (1);
}

/* Main function for parsing.
Validates the syntax of the token list, initializes the command structures,
and splits the token list into individual commands. Processes each command
and stores the information in the array of command structures.*/
int	parse_input(t_shell *sh)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = sh->first_token;
	if (!is_last_token_word(sh->first_token))
	{
		sh->cmds_array->exit_code = 258;
		return (error_input(ERR_SYNTAX_T, 0));
	}
	if (!init_array(sh->cmds_array, sh->cmd_count, sh->global_env))
		return (0);
	while (sh->first_token && i < sh->cmd_count)
	{
		if (!split_into_cmds(&sh->cmds_array[i], sh))
			return (0);
		if (!sh->cmds_array[i].cmd)
		{
			free_cmds_array_env(sh->cmds_array, sh->cmd_count);
			return (0);
		}
		i++;
	}
	sh->first_token = temp;
	return (1);
}
