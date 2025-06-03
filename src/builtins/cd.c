/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:43 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/03 18:42:32 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/execution.h"

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
char *cd_builtin(char *path, char *cwd, size_t cwd_size)
{
	if (chdir(path) == 0)
	{
		if (getcwd(cwd, cwd_size) != NULL)
			printf("Moved to: %s\n", cwd); 
		else
			perror("getcwd failed");
	}
	else
		perror("Invalid cd path");
	return (cwd);
}
