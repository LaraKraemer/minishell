/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:23:59 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/03 18:08:20 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../incl/execution.h"

void pwd_builtin(char *cwd, size_t cwd_size)
{
	if (getcwd(cwd, cwd_size) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd failed");
}
