/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/25 11:49:03 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "../../incl/minishell.h"

int	get_tokens(char *input, t_token **first_token,
		char **envp, int last_exit_code)
{
	t_token			*current_token;
	t_token_type	type;
	char			*value;

	while (*input)
	{
		skip_delimiter(&input);
		if (!*input)
			return (1);
		type = determine_type(input, input + 1);
		value = determine_value(type, &input, envp, last_exit_code);
		//printf("%s - value\n", value);
		if (!value)
			return (error_input(ERR_SYNTAX_T, 1));
		if (value[0] == '\0')
		{
			free(value);
			if (!*(input + 1))
				return (1);
			else
				continue ;
		}
		if (*first_token == NULL)
		{
			*first_token = ms_lstnew(type, value);
			current_token = *first_token;
		}
		else
		{
			current_token = ms_lstnew(type, value);
			ms_lstadd_back(first_token, current_token);
		}
	}
	return (0);
}

