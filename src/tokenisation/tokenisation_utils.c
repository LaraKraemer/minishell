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

#include "../../incl/tokenisation.h"
# include "Libft/libft.h"

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
	if (ft_isprint(c) && !special_character(c))
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
