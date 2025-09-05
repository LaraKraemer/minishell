/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:00:30 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/05 17:06:50 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

static int	shell_atoi(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

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
		return (print_error(args[2], ERR_ARG_SIZE), 1);
	if (args[1][i] == '-' || args[1][i] == '+')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i++]))
		{
			print_error(args[1], ERR_NUMERIC);
			exit(255);
		}
	}
	exit_code = shell_atoi(args[1]);
	exit((exit_code % 256 + 256) % 256);
}
