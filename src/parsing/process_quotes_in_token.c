/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes_in_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-08 09:16:39 by dtimofee          #+#    #+#             */
/*   Updated: 2025-08-08 09:16:39 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"

/*Parses a token and returns a new string with quotes removed and variable
expansions applied where appropriate (inside quotations).*/

static void	process_double_quotes(char **token, char **result,
		char **envp, int exit_code)
{
	(*token)++;
	while (**token && **token != '"')
	{
		if (**token == '$' && (ft_isalnum(*(*token + 1))
				|| *(*token + 1) == '_' || *(*token + 1) == '?'))
		{
			(*token)++;
			*result = do_expansion(token, envp, exit_code, *result);
		}
		else
		{
			*result = ft_strjoin_char(*result, **token);
			(*token)++;
		}
	}
}

static void	process_single_quotes(char **token, char **result)
{
	(*token)++;
	while (**token && **token != '\'')
	{
		*result = ft_strjoin_char(*result, **token);
		(*token)++;
	}
	if (**token == '\'')
		(*token)++;
}

char	*quotes_token(char *token, char **envp, int exit_code)
{
	char	*result;

	result = ft_strdup("");
	while (*token)
	{
		if (*token == '"')
			process_double_quotes(&token, &result, envp, exit_code);
		else if (*token == '\'')
			process_single_quotes(&token, &result);
		else
		{
			result = ft_strjoin_char(result, *token);
			token++;
		}
	}
	return (result);
}
