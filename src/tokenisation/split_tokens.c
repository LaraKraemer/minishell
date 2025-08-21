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
#include "libft/libft.h"

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

char	*determine_value(t_token_type type, char **start,
		char **envp, int last_exit_code)
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
