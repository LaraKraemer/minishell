/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:59:03 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/22 18:22:48 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	size_t			s1_len;
	unsigned int	i;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s1[i])
	{
		if (ft_strchr(set, s1[i]) == NULL)
			break ;
		i++;
	}
	while (s1_len > 0)
	{
		if (ft_strchr(set, s1[s1_len - 1]) == NULL)
			break ;
		s1_len--;
	}
	if (i + 1 > s1_len)
		return (ft_strdup(""));
	str = malloc((s1_len - i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + i, s1_len - i + 1);
	return (str);
}
