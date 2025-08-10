/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-07 10:15:40 by dtimofee          #+#    #+#             */
/*   Updated: 2025-08-07 10:15:40 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "libft/libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
	{
		result = ft_strdup(s2);
		return (result);
	}
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

char	*ft_strjoin_char(char *s, char c)
{
	char	*result;
	size_t	len;

	if (s)
		len = ft_strlen(s);
	else
		len = 0;
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	if (s)
		ft_memcpy(result, s, len);
	result[len] = c;
	result[len + 1] = '\0';
	free(s);
	return (result);
}

static void	handle_quotes(char **end, int *single_quote, int *double_quote)
{
	if (**end == '"')
	{
		(*double_quote)++;
		(*end)++;
		while (**end && **end != '"')
			(*end)++;
		if (**end == '"')
			(*double_quote)++;
	}
	else if (**end == '\'')
	{
		(*single_quote)++;
		(*end)++;
		while (**end && **end != '\'')
			(*end)++;
		if (**end == '\'')
			(*single_quote)++;
	}
}

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

char	*copy_words(char **start, char **envp, int last_exit_code)
{
	char		*end;
	char		*word;
	int			single_quote;
	int			double_quote;

	end = *start;
	single_quote = 0;
	double_quote = 0;
	word = NULL;
	while (*end && !correct_delimiter(*end) && !special_character(*end))
	{
		if (*end == '"' || *end == '\'')
		{
			handle_quotes(&end, &single_quote, &double_quote);
			word = ft_substr(*start, 0, end - *start);
			end++;
		}
		else if (*end == '$')
		{
			end++;
			word = do_expansion(&end, envp, last_exit_code, word);
		}
		else
		{
			word = ft_strjoin_char(word, *end);
			end++;
		}
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
	{
		free(word);
		return (NULL);
	}
	*start = end;
	return (word);
}
