/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:15:40 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/05 17:48:25 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "libft/libft.h"

/*Parses and counts single and double quotes in a string.
Moves the `end` pointer past a quoted section and increments counters.*/
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

/* 
Handles a quoted section in the input string.
Moves the end pointer past the quoted part, updates quote counters,
and returns a substring from start to the end of the quoted section.
 */
static char	*handle_quoted_part(char **end, int *single_q,
			int *double_q, char **start)
{
	handle_quotes(end, single_q, double_q);
	return (ft_substr(*start, 0, *end - *start + 1));
}

/*
Handles variable or special expansion in input string.
Moves end pointer, performs expansion, and returns the new word.
*/
static char	*handle_expansion(char **end, char **envp,
		int last_exit_code, char *word)
{
	(*end)++;
	return (do_expansion(end, envp, last_exit_code, word));
}

/*
Parses a word from the input string `*start`, calling handler for:
- quotes (`'` and `"`)
- variable expansion (`$VAR`, `$?`)
and handling itself:
- character accumulation
Stops parsing on encountering a delimiter or special character.
*/
char	*copy_words(char **start, char **envp, int last_exit_code)
{
	char	*end;
	char	*word;
	int		single_q;
	int		double_q;

	end = *start;
	word = NULL;
	single_q = 0;
	double_q = 0;
	while (*end && !correct_delimiter(*end) && !special_character(*end))
	{
		if (*end == '"' || *end == '\'')
		{
			word = handle_quoted_part(&end, &single_q, &double_q, start);
			end++;
		}
		else if (*end == '$' && (ft_isalnum(*(end + 1))
				|| *(end + 1) == '_' || *(end + 1) == '?'))
			word = handle_expansion(&end, envp, last_exit_code, word);
		else
			word = ft_strjoin_char(word, *end++);
	}
	if (double_q % 2 != 0 || single_q % 2 != 0)
		return (free(word), NULL);
	return (*start = end, word);
}

/* char	*copy_words(char **start, char **envp, int last_exit_code)
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
			word = ft_substr(*start, 0, end - *start + 1);
			end++;
		}
		else if (*end == '$' && (ft_isalnum(*(end + 1))
				|| *(end + 1) == '_' || *(end + 1) == '?'))
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
} */
