/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:23 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/04 17:58:20 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// REPL
// READ - Evaluate - Print/ Execute - Loop
int	main(int argc, char **argv, char **envp)
{

	char		*input;
	char		*raw_input = NULL;
	t_token		*first_token;
	int			cmd_count;
	t_command	*cmds_array;
	int			exit_status;
	int			i;

	(void)argc;
	(void)argv;
	exit_status = 0;
	print_banner();
	while (1)
	{
		raw_input = readline("testshell>$ ");
		if (!raw_input) {
			printf("EOF");
			break;
			}
		i = 0;
		// White space trimmer
		input = ft_strtrim(raw_input, " \t\n");
		free(raw_input);
		if (!input || !*input)
		{
			free(input);
			continue;
		}
		if (*input)
			add_history(input);
		printf("Raw input: \"%s\"\n", input);
		// Tokenizer 
		first_token = NULL;
		if (get_tokens(input, &first_token))
			continue ;
		t_token *current;
		current = first_token;
		while (current)
		{
			printf("Splitted token: %s\n", current->value);
			current = current->next;
		}
		cmd_count = count_cmd_num(first_token);
		cmds_array = malloc((cmd_count) * sizeof(t_command));
		if (!cmds_array)
		{
			error_input("malloc failed", 1);
			continue ;
		}
		// Parser
		if (!parse_input(cmds_array, first_token, cmd_count, envp))
		{
			free (cmds_array);
			continue ;
		}
		// Debug printer 
        for (int i = 0; i < cmd_count; i++) {
            printf("CMD %d: %s\n", i, cmds_array[i].cmd);
            printf("  ARGS:");
            for (int j = 0; cmds_array[i].cmd_args[j]; j++)
                printf(" [%s]", cmds_array[i].cmd_args[j]);
            printf("\n");
        }
		while (i < cmd_count)
		{
			if (set_path(&cmds_array[i], envp) == -1)
			{
				error_input("Failed to set PATH", 127);
				break;
			}
			i++;
		}
		/* printf("Initial ENVP:\n");
		for (int j = 0; envp[j]; j++)
    		printf("%s\n", envp[j]); */
		// Executing builtins
		if (cmd_count == 1 && is_builtin(cmds_array[0].cmd_args[0]))
        {
            if (must_run_in_parent(cmds_array[0].cmd_args[0]))
            {
                exit_status = builtins(cmds_array, envp);
                free_resources(input, cmds_array, cmd_count);
                continue;
            }
        }
		// Executing everything else
		exit_status = execute_with_pipex_logic(cmds_array, cmd_count, envp);
		free_resources(input, cmds_array, cmd_count);
	}
	return (exit_status);
}






/* 
// printf("cmd count - %d\n", cmd_count);
		// fflush(0);
		

if (cmd_count > 1)
		{
			pipe_fds = malloc((cmd_count - 1) * 2 * sizeof(int));
			int i = 0;
			while (i < cmd_count - 1) 
			{
				if (pipe(pipe_fds + i*2) == -1) 
				{
					perror("pipe");
					exit(1);
				}
				i++;
			}
		} */
		/* if (cmd_count > 1)
		{
			if (!fill_pipes_fd(pipe_fds, cmd_count))
			{
				free(cmds_array);
				continue ;
			}
		} */
		//free(args);


		
// char **args = cell_split_input(input);
		// builtins(args, env);
		// non_builtins(args, env);
		// int i = 0;
		// while (args[i])
		// {
		// 	printf("Token[%d]: %s\n",i,  args[i]);
		// 	i++;
		// }
		
