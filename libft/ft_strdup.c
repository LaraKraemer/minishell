/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:19:39 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/18 17:57:01 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*dest;
	size_t			s_len;
	unsigned int	i;

	i = 0;
	s_len = ft_strlen(s);
	dest = (char *)malloc((s_len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	else
	{
		while (s_len >= i)
		{
			dest[i] = s[i];
			i++;
		}
	}
	return (dest);
}
