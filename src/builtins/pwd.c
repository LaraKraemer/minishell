/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:23:59 by lkramer           #+#    #+#             */
/*   Updated: 2025/08/21 15:13:49 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/*
Runs in child process - no issues with forking since
it doesn’t change anything.
*/
int	pwd_builtin(char *cwd, size_t cwd_size)
{
	if (getcwd(cwd, cwd_size) != NULL)
		printf("%s\n", cwd);
	else
	{
		sys_error("getcwd", cwd);
		return (1);
	}
	return (0);
}
