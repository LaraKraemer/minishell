/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025-05-27 10:38:57 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_tokens(char *input)
{
	t_token	*first_token;
	t_token	*current_token;

	while (*input)
	{
		skip_delimiter(&input);

	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	// argv[argc] = NULL;
	// printf("%s\n", env[0]);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		//printf("%s\n", input);
		if (*input)
			add_history(input); //what if it will be just space in input line?
		get_tokens(input);
		free(input);
	}
	//return EXIT_SUCCESS;
	//exit(0); //need to exit with the correct exit code
}
