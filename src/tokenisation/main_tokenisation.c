/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 17:53:26 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "../../incl/minishell.h"

static int	handle_empty_value(char **value, char *input)
{
	if (!*(input + 1))
		return (1);
  free(*value);
	return (-1);
}

static void	add_new_token(t_token **first_token, t_token **current_token,
				t_token_type type, char *value)
{
	if (*first_token == NULL)
	{
		*first_token = ms_lstnew(type, value);
		*current_token = *first_token;
	}
	else
	{
		*current_token = ms_lstnew(type, value);
		ms_lstadd_back(first_token, *current_token);
	}
}

int	get_tokens(char *input, t_token **first_token,
			char **envp, int last_exit_code)
{
	t_token			*current_token;
	t_token_type	type;
	char			*value;
	int				result;
	char			*original_input;

	original_input = input;
	while (*input)
	{
		skip_delimiter(&input);
		if (!*input)
			return (1);
		type = determine_type(input, input + 1);
		value = determine_value(type, &input, envp, last_exit_code);
		if (!value)
		{
			free_if_error(original_input, first_token);
			return (error_input(ERR_SYNTAX_T, 1));
		}
		if (value[0] == '\0')
		{
			result = handle_empty_value(&value, input);
			if (result != -1)
				return (free_if_error(original_input, first_token), result);
			continue ;
		}
		add_new_token(first_token, &current_token, type, value);
	}
	return (0);
}
