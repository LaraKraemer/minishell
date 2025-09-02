/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:26:12 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/18 19:23:16 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	size_t				i;

	src = s;
	i = 0;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
