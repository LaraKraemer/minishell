/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-30 08:53:13 by dtimofee          #+#    #+#             */
/*   Updated: 2025-05-30 08:53:13 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	correct_delimiter(int c)
{
	if (c == 9 || c == 10 || c == 32)
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
