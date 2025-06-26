/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:23 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/11 16:06:24 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// char	**cell_split_input(char *input)
// {
// 	char			**tokens;
// 	unsigned int	position;
// 	size_t			bufsize;
// 	char			*token;

// 	bufsize = BUFSIZ;
// 	tokens = malloc(bufsize * sizeof * tokens);
// 	if (!tokens) {
//         perror("malloc failed");
//         exit(EXIT_FAILURE);
// 	}
// 	position = 0;
// 	token = strtok(input, DEL);
// 	while(token != NULL)
// 	{
// 		tokens[position++] = token;
// 		if(position >= bufsize)
// 		{
// 			bufsize *= 2;
// 			tokens = realloc(tokens, bufsize * sizeof(char *));
// 			 if (!tokens) {
//                 perror("realloc failed");
//                 exit(EXIT_FAILURE);
//             }
// 		}
// 		token = strtok(NULL, DEL);
// 	}
// 	tokens[position] = NULL;
// 	return tokens;
// }

// REPL
// READ - Evaluate - Print/ Execute - Loop
int	main(int argc, char **argv, char **envp)
{

	char		*input;
	t_token		*first_token;
	int			cmd_count;
	t_command	*cmds_array;
	int			*pipe_fds;

	argv[argc] = "h";
	envp[0] = "h";
	print_banner();
	while (1)
	{
		input = readline("testshell>$ ");
		if (!input) {
			printf("EOF");
			break;
			}
		if (*input)
			add_history(input);

		// char **args = cell_split_input(input);
		// builtins(args, env);
		// non_builtins(args, env);
		// int i = 0;
		// while (args[i])
		// {
		// 	printf("Token[%d]: %s\n",i,  args[i]);
		// 	i++;
		// }
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
		// printf("cmd count - %d\n", cmd_count);
		// fflush(0);
		cmds_array = malloc((cmd_count) * sizeof(t_command));
		if (!cmds_array)
		{
			error_input("malloc failed", 1);
			continue ;
		}
		if (!parse_input(cmds_array, first_token, cmd_count, envp))
		{
			free (cmds_array);
			continue ;
		}
		if (cmd_count > 1)
		{
			if (!fill_pipes_fd(pipe_fds, cmd_count))
			{
				free(cmds_array);
				continue ;
			}
		}
		//free(args);
		free(input);
	}
	return 0;
}
