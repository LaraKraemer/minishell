/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 14:59:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025-06-12 14:59:13 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "../../incl/parsing.h"

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

int	in_out_redir(t_command *cmd, t_token **current_token)
{
	int	current_type;

	if (!(*current_token)->next || (*current_token)->next->type != TOKEN_WORD)
		return (error_input("syntax error", 0));
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
			//start->value = check_quotes(start->value);
			cmd->cmd = start->value;
			i = 0;
			// printf("%s - cmd\n", cmd->cmd);
			// fflush(0);
			cmd->cmd_args = malloc(MAX_ARGS * sizeof(char *));
			if (!cmd->cmd_args)
				return (error_input("malloc failed", 0));
			cmd->cmd_args[i++] = start->value;
			printf("%s - cmd_arg\n", cmd->cmd_args[i - 1]);
			// fflush(0);
			while (start->next && start->next->type == TOKEN_WORD)
			{
				start = start->next;
				cmd->cmd_args[i++] = start->value;
				printf("%s - cmd_arg\n", cmd->cmd_args[i - 1]);
			}
			cmd->cmd_args[i] = NULL;
			printf("%s - cmd_arg\n", cmd->cmd_args[i - 1]);
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

void	init_array(t_command *cmds_array, int cmd_count, char **envp)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		cmds_array[i].cmd = NULL;
		cmds_array[i].cmd_args = NULL;
		cmds_array[i].env = envp;
		cmds_array[i].fd_in = -1;
		cmds_array[i].fd_out = -1;
		i++;
		//pipe_fd are not filled
	}
	//cmds_array[i] = NULL;
}

int	parse_input(t_command *cmds_array, t_token *first_token, int cmd_count, char **envp)
{
	int	i;

	i = 0;
	if (!is_last_token_word(first_token))
	{
		// printf("last token not word\n");
		return (error_input("syntax error", 0));
	}
	init_array(cmds_array, cmd_count, envp);
	while (first_token && i < cmd_count)
	{
		if (!split_into_cmds(&cmds_array[i], &first_token))
			return (0);
		if (!cmds_array[i].cmd)
			return (error_input("syntax error", 0));
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
