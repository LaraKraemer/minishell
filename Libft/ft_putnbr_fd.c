/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-22 22:35:11 by dtimofee          #+#    #+#             */
/*   Updated: 2024-11-22 22:35:11 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		digit;
	char		str[100];
	signed int	i;

	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	if (n < 0 && n != INT_MIN)
	{
		n *= (-1);
		write(fd, "-", 1);
	}
	i = 0;
	while (n >= 0)
	{
		digit = n % 10 + '0';
		n = n / 10;
		str[i++] = digit;
		if (n == 0)
			break ;
	}
	while (i - 1 >= 0)
		write(fd, &str[(i--) - 1], 1);
}
