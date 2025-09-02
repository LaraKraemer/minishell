/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:57:24 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/18 12:05:25 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//The bzero() function writes n zeroed bytes to the string s.
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*prt;
	unsigned int	i;

	prt = s;
	i = 0;
	while (i < n)
	{
		prt[i] = 0;
		i++;
	}
}
