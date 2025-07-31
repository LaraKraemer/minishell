/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:23 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 13:49:03 by lkramer          ###   ########.fr       */
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
	global_env = copy_env(envp);
	if (!global_env)
		return (error_input("malloc", 0));
	minishell_loop(&sh, &global_env);
	final_exit_code = sh.exit_code;
	free(global_env);
	return (final_exit_code);
}

/* 
// REPL
// READ - Evaluate - Print/ Execute - Loop
int	main(int argc, char **argv, char **envp)
{

	char		*input;
	char		*raw_input = NULL;
	t_token		*first_token;
	int			cmd_count;
	t_command	*cmds_array = NULL;
	int			exit_code;
	char 		**global_env = NULL;
	int			error_in_setup = 0;
	int			i;

	(void)argc;
	(void)argv;
	global_env = copy_env(envp);
	if (!global_env)
		return (error_input("malloc", 0));
	exit_code = 0;
	print_banner();
	while (1)
	{
		error_in_setup = 0;
		raw_input = readline("minishell🐣>$ ");
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
		// Tokenizer
		first_token = NULL;
		if (get_tokens(input, &first_token))
			continue ;
		cmd_count = count_cmd_num(first_token);
		cmds_array = malloc((cmd_count + 1) * sizeof(t_command));
		if (!cmds_array)
		{
			error_input(ERR_MEM_ALLO, 1);
			continue ;
		}
		// Parser
		if (!parse_input(cmds_array, first_token, cmd_count, global_env))
		{
			exit_code = 258;
			free (cmds_array);
			continue ;
		}
		i = 0;
		while (i < cmd_count)
		{
			if (set_path(&cmds_array[i], global_env) == -1)
			{
				error_input(ERR_PATH, 127);
				exit_code = 127;
				error_in_setup = 1;
				break;
			}
			i++;
		}
		if (error_in_setup) 
		{
			free_resources(input, cmds_array, cmd_count);
			continue ;
		}	
		// Executing builtins
		if (cmd_count == 1 && is_builtin(cmds_array[0].cmd_args[0]))
        {
			exit_code = builtins(&cmds_array[0], &global_env, exit_code);
			free_resources(input, cmds_array, cmd_count);
			continue;
        }
		// Executing everything else
		exit_code = execute_with_pipex_logic(cmds_array, cmd_count);
		free_resources(input, cmds_array, cmd_count);
	}
	free(global_env);
	return (0);
} */
/* 
t_token *current;
current = first_token;
while (current)
{
	// printf("Splitted token: %s\n", current->value);
	current = current->next;
}

// printf("Raw input: \"%s\"\n", input);


// Debug printer
for (int i = 0; i < cmd_count; i++) 
{
	printf("CMD %d: %s\n", i, cmds_array[i].cmd);
	printf("  ARGS:");
	int j;
	for (j = 0; cmds_array[i].cmd_args[j]; j++)
		printf(" [%s]", cmds_array[i].cmd_args[j]);
	if (cmds_array[i].cmd_args[j] == NULL)
		printf(" [NULL]");
	printf("\n");
} 
		
if (must_run_in_parent(cmds_array[0].cmd_args[0]))
{ 
	exit_code = builtins(&cmds_array[0], &global_env, exit_code);
	free_resources(input, cmds_array, cmd_count);
	continue;
}

// printf("DEBUG: execute_with_pipex_logic returned: %d\n", exit_code);
// printf("DEBUG: execute_with_pipex_logic expanding: %d\n", exit_code);

printf("Initial ENVP:\n");
for (int j = 0; envp[j]; j++)
	printf("%s\n", envp[j]);


			
*/