/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:52:51 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/28 15:46:41 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_separator(const char **s, char c)
{
	while (**s == c && **s)
	{
		(*s)++;
	}
}

int	count_words(const char *s, char c)
{
	unsigned int	counter;

	counter = 0;
	while (*s)
	{
		skip_separator(&s, c);
		if (*s != c && *s != '\0')
		{
			counter++;
			while (*s != c && *s != '\0')
			{
				s++;
			}
		}
	}
	return (counter);
}

static char	*copy_word(const char **start, char c)
{
	const char	*end;
	char		*word;
	size_t		word_len;

	end = *start;
	while (*end != c && *end != '\0')
	{
		end++;
	}
	word_len = end - *start;
	word = malloc((word_len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	ft_memcpy(word, *start, word_len);
	word[word_len] = '\0';
	*start = end;
	return (word);
}

static char	**free_array(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		free (str_array[i++]);
	free (str_array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**str_array;
	char const		*src;
	unsigned int	i;
	unsigned int	words_count;

	if (s == NULL)
		return (NULL);
	src = s;
	words_count = count_words(s, c);
	str_array = malloc((words_count + 1) * sizeof(char *));
	if (str_array == NULL)
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		skip_separator(&src, c);
		str_array[i] = copy_word(&src, c);
		if (str_array[i] == NULL)
			return (free_array(str_array));
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}
