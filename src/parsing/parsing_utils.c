/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-04 09:57:45 by dtimofee          #+#    #+#             */
/*   Updated: 2025-06-04 09:57:45 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"

int	correct_delimiter(int c)
{
	if (c == 9 || c == 10 || c == 32)
		return (1);
	return (0);
}

int	special_character(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_word_token_start(int c)
{
	if (ft_isalnum(c) || c == '"' || c == '\'' || c == '-'
		|| c == '.' || c == '/')
		return (1);
	return (0);
}

void	skip_delimiter(char **s)
{
	while (correct_delimiter(**s) && **s)
	{
		(*s)++;
	}
}
