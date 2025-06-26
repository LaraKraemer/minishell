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

char	*copy_words(char **start)
{
	char		*end;
	char		*word;
	size_t		word_len;
	int			single_quote;
	int			double_quote;

	end = *start;
	single_quote = 0;
	double_quote = 0;
	while (!correct_delimiter(*end) && !special_character(*end) && *end)
	{
		if (*end == '"' || *end == '\'')
			handle_quotes(&end, &single_quote, &double_quote);
		end++;
	}
	if (double_quote % 2 != 0 || single_quote % 2 != 0)
		return (NULL);
	word_len = end - *start;
	word = malloc((word_len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, *start, word_len);
	word[word_len] = '\0';
	*start = end;
	return (word);
}

char	*determine_value(t_token_type type, char **start)
{
	char	*copy_start;

	copy_start = *start;
	if (type == TOKEN_WORD)
		return (copy_words(start));
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
