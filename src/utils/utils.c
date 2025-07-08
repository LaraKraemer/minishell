/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:25:14 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/04 16:30:50 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_banner(void)
{
	printf(".######..######...####...######...####...##..##..######..##......##.....\n"
		   "...##....##......##........##....##......##..##..##......##......##.....\n"
		   "...##....####.....####.....##.....####...######..####....##......##.....\n"
		   "...##....##..........##....##........##..##..##..##......##......##.....\n"
		   "...##....######...####.....##.....####...##..##..######..######..######.\n"
		   "........................................................................\n");
}

/* void free_tokens(t_token *tokens)
{
    t_token *tmp;
    while (tokens) {
        tmp = tokens;
        tokens = tokens->next;
        free(tmp->value);
        free(tmp);
    }
} */

void	free_resources(char *input, t_command *cmds, int count)
{
    free(input);
    // free_tokens(tokens);
    free_commands(cmds, count);
}

// t_token *tokens


/* 
 * Creates a copy of the environment variables

static char	**copy_environment(char **envp)
{
	char	**new_env;
	size_t	count;
	size_t	i;

	if (!envp || !*envp)
		return (NULL);
	
	// Count environment variables
	count = 0;
	while (envp[count])
		count++;
	
	// Allocate array + NULL terminator
	new_env = (char **)malloc((count + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	
	// Copy each string
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			// Cleanup on failure
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
} 
*/