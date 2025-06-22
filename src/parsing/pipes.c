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

// int	fill_pipes_fd(t_command *cmds_array, int cmd_count)
// {
// 	int	i;

// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		if (pipe(cmds_array[i].pipe_fd) == -1)
// 		{
// 			perror("pipe");
// 			return (0);
// 		}
// 		cmds_array[i].fd_out = cmds_array[i].pipe_fd[1];
// 		cmds_array[i + 1].fd_in = cmds_array[i].pipe_fd[0];
// 		i++;
// 	}
// 	r
// }
