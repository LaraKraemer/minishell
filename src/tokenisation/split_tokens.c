/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 08:53:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/02 17:19:32 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
# include "Libft/libft.h"

t_token_type	determine_type(char *start, char *next)
{
	if (is_word_token_start(*start))
		return (TOKEN_WORD);
	else if (*start == '|')
		return (TOKEN_PIPE);
	else if (*start == '<' && *next != '<')
		return (TOKEN_REDIR_IN);
	else if (*start == '>' && *next != '>')
		return (TOKEN_REDIR_OUT);
	else if (*start == '>' && *next == '>')
		return (TOKEN_APPEND);
	else if (*start == '<' && *next == '<')
		return (TOKEN_HEREDOC);
	return (TOKEN_UNKNOWN);
}

static void	handle_quotes(char **end, int *single_quote, int *double_quote)
{
	if (**end == '"')
	{
		(*double_quote)++;
		(*end)++;
		while (**end != '"' && **end)
			(*end)++;
		if (**end == '"')
			(*double_quote)++;
	}
	else if (**end == '\'')
	{
		(*single_quote)++;
		(*end)++;
		while (**end != '\'' && **end)
			(*end)++;
		if (**end == '\'')
			(*single_quote)++;
	}
}

char	*copy_words(char **start, char **envp, int last_exit_code)
{
	char		*end;
	char		*word;
	char		*expanded_value;
	//size_t		word_len;
	int			single_quote;
	int			double_quote;

	end = *start;
	single_quote = 0;
	double_quote = 0;
	word = NULL;
	//word = ft_strdup("");
	while (*end && !correct_delimiter(*end) && !special_character(*end))
	{
		if (*end == '"' || *end == '\'')
			handle_quotes(&end, &single_quote, &double_quote);
		else if (*end == '$') // Обработка $ expansion
		{
			end++;
			expanded_value = expand_variable(end, envp, last_exit_code);
			// if (!expanded_value)
			// 	return (NULL);
			word = ft_strjoin_free(word, expanded_value);
			free(expanded_value);
			if (*end != '?')
			{
				while (*end && (ft_isalnum(*end) || *end == '_'))
					end++;
			}
			else
			// {
			// 	if (*end)
					end++;
			//}
		}
		else
		{
			word = ft_strjoin_char(word, *end); // ft_strjoin_char добавляет символ к строке
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

char	*determine_value(t_token_type type, char **start, char **envp, int last_exit_code)
{
	char	*copy_start;

	copy_start = *start;
	if (type == TOKEN_WORD)
		return (copy_words(start, envp, last_exit_code));
	else if (type == TOKEN_PIPE || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_OUT)
	{
		(*start)++;
		return (ft_substr(copy_start, 0, 1));
	}
	else if (type == TOKEN_APPEND || type == TOKEN_HEREDOC)
	{
		(*start) += 2;
		return (ft_substr(copy_start, 0, 2));
	}
	else
		return (NULL);
}
