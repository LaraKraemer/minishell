/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:00:30 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/16 16:20:49 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Runs in parent process - since it exit shell.
# one cmd run in parent process 
# two run in child process 
*/
int	exit_builtin(char **args)
{
	int	i;
	int	exit_code;

	i = 0;
	if (!args[1])
		exit(0);
	if (args[2])
	{
		ft_putstr_fd(ERR_ARG_SIZE, 2);
		return (1);
	}
	if (args[1][i] == '-' || args[1][i] == '+')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i++]))
		{
			ft_putstr_fd("testshell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
	}
	exit_code = ft_atoi(args[1]);
	exit(exit_code % 256);
}
