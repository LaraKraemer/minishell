/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:43 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/11 13:54:30 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/* 
Relative path:
A path relative to the current working directory.
cd .. → go up one directory.
cd ../folder
cd subdir → go into a subdirectory in the current directory.

Absolute path:
A path that starts from the root of the filesystem.
cd /users/lara/
cd /var/log
cd / → go to the root directory.
*/
int	cd_builtin(char *args)
{
	if (!args)
	{
		if (!getenv("HOME"))
			ft_putstr_fd(ERR_CD, 2);
		return (1);
	}
	if (chdir(args) == -1)
	{
		perror("cd failed");
		return (1);
	}
	return (0);
}
