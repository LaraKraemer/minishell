/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:28:14 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/22 17:57:27 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t					i;
	const unsigned char		*src1;
	const unsigned char		*src2;

	i = 0;
	src1 = (const unsigned char *) s1;
	src2 = (const unsigned char *) s2;
	while ((src1[i] || src2[i]) && i < n)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	return (0);
}
