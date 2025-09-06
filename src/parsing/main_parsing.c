/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:59:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 20:57:21 by 123              ###   ########.fr       */
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

/*Processes the token list and extracts information for a single command
 (command name, arguments, redirections). Updates the command structure
 and moves the token pointer to the next command.*/
int	split_into_cmds(t_command *cmd, t_token **first_token,
		char **envp, int ex_code)
{
	t_token	*start;
	int		i;
	int		return_from_redirections;

	start = *first_token;
	i = 0;
	cmd->cmd_args = malloc(MAX_ARGS * sizeof(char *));
	if (!cmd->cmd_args)
		return (error_input(ERR_MEM_ALLO, 0));
	while (start && start->type != TOKEN_PIPE)
	{
		if (start->type == TOKEN_REDIR_IN || start->type == TOKEN_REDIR_OUT
			|| start->type == TOKEN_APPEND || start->type == TOKEN_HEREDOC)
		{
			return_from_redirections = in_out_redir(cmd, &start, envp, ex_code);
			if (return_from_redirections == 0)
			{
				cmd->exit_code = 130;
				free_commands(cmd, count_cmd_num(*first_token));
				return (0);
			}
			else if (return_from_redirections == -1)
			{
				cmd->exit_code = 1;
				while (start->next && start->next->type != TOKEN_PIPE)
					start = start->next;
				continue ;
			}
		}
		else if (start->type == TOKEN_WORD)
		{
			if (!cmd->cmd)
				cmd->cmd = quotes_token(start->value, envp, ex_code);
			cmd->cmd_args[i++] = quotes_token(start->value, envp, ex_code);
		}
		start = start->next;
	}
	cmd->cmd_args[i] = NULL;
	if (start)
		start = start->next;
	*first_token = start;
	return (1);
}

/* Main function for parsing.
Validates the syntax of the token list, initializes the command structures,
and splits the token list into individual commands. Processes each command
and stores the information in the array of command structures.*/
int	parse_input(t_command *cmds_array, t_token *first_token,
		int cmd_count, int exit_code, char **envp)
{
	int		i;

	i = 0;
	if (!is_last_token_word(first_token))
	{
		cmds_array->exit_code = 258;
		return (error_input(ERR_SYNTAX_T, 0));
	}
	if (!init_array(cmds_array, cmd_count, envp))
		return (0);
	while (first_token && i < cmd_count)
	{
		if (!split_into_cmds(&cmds_array[i], &first_token, envp, exit_code))
			return (0);
		if (!cmds_array[i].cmd) //возможно тут нужно что-то почистить
		{
			free_cmds_array_env(cmds_array, cmd_count);
			return (error_input(ERR_SYNTAX_T, 0));
		}
		i++;
	}
	return (1);
}
