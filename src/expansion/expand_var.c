/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:57:53 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 17:49:04 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "libft/libft.h"

char	*expand_variable(char *start, char **envp, int last_exit_code)
{
	char	*var_name;
	char	*expanded_value;
	size_t	var_len;

	if (*start == '?')
	{
		expanded_value = ft_itoa(last_exit_code);
		return (expanded_value);
	}
	else
	{
		var_len = 0;
		while (start[var_len] && (ft_isalnum(start[var_len])
				|| start[var_len] == '_'))
			var_len++;
		var_name = ft_substr(start, 0, var_len);
		expanded_value = get_env_value(var_name, envp);
		free(var_name);
		return (expanded_value);
	}
}

/*Handles environment variable or special variable (`$?`) expansion.
Extracts variable name from `*end`, finds its value in `envp`,
and appends the expanded value to the current `word`.*/
char	*do_expansion(char **end, char **envp, int last_exit_code, char *word)
{
	char	*result;
	char	*expanded_value;
	char	*current;

	current = *end;
	expanded_value = expand_variable(current, envp, last_exit_code);
	result = ft_strjoin_free(word, expanded_value);
	free(expanded_value);
	if (*current != '?')
	{
		while (*current && (ft_isalnum(*current) || *current == '_'))
			current++;
	}
	else
		current++;
	*end = current;
	return (result);
}
