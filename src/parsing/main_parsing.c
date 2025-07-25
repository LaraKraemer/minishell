/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:59:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/25 11:45:48 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
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

/*Checks the redirection types (input, output, append) and opens the
 corresponding files. Updates the file descriptors (fd_in, fd_out)
 in the command structure. Also checks for errors if there is redirection
 but without filename*/
int	in_out_redir(t_command *cmd, t_token **current_token)
{
	int	current_type;

	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		return (error_input(ERR_SYNTAX_T, 0));
	current_type = -1;
	if ((*current_token)->type == TOKEN_REDIR_IN)
	{
		current_type = (*current_token)->type;
		*current_token = (*current_token)->next;
		if (cmd->fd_in != -1)
			close(cmd->fd_in);
		// printf("%s - input file\n", (*current_token)->value);
		// fflush(0);
		// if (!open_file(cmd, (*current_token)->value, 0))
		// 	return (0);
	}
	else if ((*current_token)->type == TOKEN_REDIR_OUT || (*current_token)->type == TOKEN_APPEND)
	{
		current_type = (*current_token)->type;
		*current_token = (*current_token)->next;
		if (cmd->fd_out != -1)
			close(cmd->fd_out);
		// if (!open_file(cmd, (*current_token)->value, 1))
		// 	return (0);
	}
	if (!open_file(cmd, (*current_token)->value, current_type))
		return (0);
	return (1);
}

/*Processes the token list and extracts information for a single command
 (command name, arguments, redirections). Updates the command structure
 and moves the token pointer to the next command.*/
int	split_into_cmds(t_command *cmd, t_token **first_token)
{
	t_token	*start;
	int		i;

	start = *first_token;
	// printf("%s - start value\n", start->value);
	// fflush(0);
	while (start && start->type != TOKEN_PIPE)
	{
		// printf("%d - token type\n", start->type);
		// fflush(0);
		if (start->type == TOKEN_REDIR_IN || start->type == TOKEN_REDIR_OUT
			|| start->type == TOKEN_APPEND)
		{
			if (!in_out_redir(cmd, &start))
				return (0);
		}
		else if (start->type == TOKEN_WORD)
		{
			cmd->cmd = start->value;
			i = 0;
			// printf("%s - cmd\n", cmd->cmd);
			// fflush(0);
			cmd->cmd_args = malloc(MAX_ARGS * sizeof(char *));
			if (!cmd->cmd_args)
				return (error_input(ERR_MEM_ALLO, 0));
			cmd->cmd_args[i++] = start->value;
			// printf("%s - cmd_arg\n", cmd->cmd_args[i - 1]);
			// fflush(0);
			while (start->next && start->next->type == TOKEN_WORD)
			{
				start = start->next;
				cmd->cmd_args[i++] = start->value;
				printf("%s - cmd_arg\n", cmd->cmd_args[i - 1]);
			}
			cmd->cmd_args[i] = NULL;
		}
		// printf("%s - last token value\n", start->value);
		if (start)
			start = start->next;
		// printf("%p - pointer to last token\n", start);
		// fflush(0);
	}
	if (start)
		start = start->next;
	// printf("%p - pointer to last token\n", start);
	// fflush(0);
	*first_token = start;
	// printf("%p - pointer to last token\n", start);
	// fflush(0);
	// if (*first_token)
	// 	printf("%s - first token value\n", (*first_token)->value);
	// fflush(0);
	return (1);
}

/*Initializes an array of command structures.*/
int	init_array(t_command *cmds_array, int cmd_count, char **envp)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		cmds_array[i].cmd = NULL;
		cmds_array[i].cmd_args = NULL;
		/* cmds_array[i].env = envp; */
		cmds_array[i].env = copy_env(envp);
		if (!cmds_array[i].env)
			return (error_input(ERR_MEM_ALLO, 0));
		cmds_array[i].fd_in = -1;
		cmds_array[i].fd_out = -1;
		cmds_array[i].path_file = NULL;
		cmds_array[i].cmd_path = NULL;
		cmds_array[i].exit_code = 0;
		i++;
	}
	cmds_array[i].cmd = NULL;
	return (1);
}

/* Main function for parsing.
Validates the syntax of the token list, initializes the command structures,
and splits the token list into individual commands. Processes each command
and stores the information in the array of command structures.*/
int	parse_input(t_command *cmds_array, t_token *first_token, int cmd_count, char **envp)
{
	int		i;

	i = 0;
	if (!is_last_token_word(first_token))
	{
		// printf("last token not word\n");
		return (error_input(ERR_SYNTAX_T, 0));
	}
	if (!init_array(cmds_array, cmd_count, envp))
		return (0);
	// if (!do_expansion(first_token))
	// 	return (0);
	// printf("%s - first token value\n", first_token->value);
	while (first_token && i < cmd_count)
	{
		if (!split_into_cmds(&cmds_array[i], &first_token))
			return (0);
		if (!cmds_array[i].cmd)
			return (error_input(ERR_SYNTAX_T, 0));
		// if (first_token)
		// 	first_token++;
		printf("%s - cmd %d\n", cmds_array[i].cmd, i);
		// if (first_token)
		// 	printf("%s - first token value\n", first_token->value);
		// fflush(0);
		i++;
	}
	return (1);
}
