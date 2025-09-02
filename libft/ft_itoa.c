/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:58:00 by dtimofee          #+#    #+#             */
/*   Updated: 2024/11/22 17:34:29 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_elements(int n)
{
	unsigned int	counter;

	counter = 0;
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static char	*write_numbers(char *str, int n, int num_elements)
{
	unsigned int	i;

	str[num_elements] = '\0';
	i = num_elements - 1;
	if (n < 0)
		n *= (-1);
	while (n >= 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
		num_elements--;
		if (n == 0)
			break ;
	}
	if (num_elements > 0)
		str[i] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	num_elements;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num_elements = count_elements(n);
	str = malloc((num_elements + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	return (write_numbers(str, n, num_elements));
}
