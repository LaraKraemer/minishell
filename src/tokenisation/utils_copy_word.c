/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_copy_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:42:39 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/05 17:42:59 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "libft/libft.h"

/*Concatenates two strings s1 and s2 into a new string.
Frees s1 after the concatenation.*/
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

/*Appends a single character c to the end of a given string s.
Frees the original string s and returns the new string.*/
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
