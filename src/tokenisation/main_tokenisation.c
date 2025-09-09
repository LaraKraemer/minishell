/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/09 09:32:54 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "../../incl/minishell.h"

static int	handle_empty_value(char **value, char *input)
{
	free(*value);
	if (!*(input + 1))
		return (1);
	return (-1);
}

static void	add_new_token(t_token **first_token,
						t_token **current_token,
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

static int	handle_value(char **value, char **input)
{
	int	result;

	if (!*value)
		return (2);
	if (!(*value)[0])
	{
		result = handle_empty_value(value, *input);
		if (result == -1)
			return (-1);
		return (result);
	}
	return (0);
}

static int	create_token_info(char **input, char **env,
						int exit_code, t_token **first_token)
{
	t_token_type	type;
	char			*value;
	int				result;
	t_token			*current_token;

	type = determine_type(*input, *input + 1);
	value = determine_value(type, input, env, exit_code);
	result = handle_value(&value, input);
	if (result == -1 || result != 0)
		return (result);
	add_new_token(first_token, &current_token, type, value);
	return (0);
}

int	get_tokens(char *input, t_token **first_token,
				char **envp, int exit_code)
{
	char	*oinput;
	int		result;

	oinput = input;
	while (*input)
	{
		skip_delimiter(&input);
		if (!*input)
			return (1);
		result = create_token_info(&input, envp, exit_code, first_token);
		if (result == -1)
			continue ;
		if (result == 2)
			return (free_if_error(oinput, first_token),
				error_input(ERR_SYNTAX_T, 1));
		if (result != 0)
			return (free_if_error(oinput, first_token), result);
	}
	return (0);
}
