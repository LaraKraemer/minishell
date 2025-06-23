/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-22 11:46:22 by dtimofee          #+#    #+#             */
/*   Updated: 2025-06-22 11:46:22 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "../../incl/parsing.h"

int	fill_pipes_fd(int *pipe_fds, int cmd_count)
{
	int	i;

	pipe_fds = malloc((cmd_count - 1) * 2 * sizeof(int));
	if (!pipe_fds)
		return (error_input("malloc failed", 0));
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(&pipe_fds[2 * i]) == -1)
			return (error_input("pipe failed", 0));
		i++;
	}
	return (1);
}

