/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:23:59 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/11 11:55:43 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

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
