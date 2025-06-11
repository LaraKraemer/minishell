/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:53:19 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/11 11:52:26 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
echo hello world
Output: hello world\n
echo -n hello
Output: hello (No Trailing newline)
No errors - always returns 0
*/
int	echo_builtin(char **path)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (path[1] && ft_strcmp(path[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (path[i])
	{
		printf("%s", path[i]);
		if (path[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
