/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:23:59 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/12 13:58:16 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Runs in child process - no issues with forking since 
it doesn’t change anything.
*/
int	pwd_builtin(char **args, char *cwd, size_t cwd_size)
{
	if (args[1] != NULL)
	{
		ft_putstr_fd(ERR_ARG_SIZE, 2);
		return (1);
	}
	if (getcwd(cwd, cwd_size) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("getcwd failed");
		return (1);
	}
	return (0);
}
