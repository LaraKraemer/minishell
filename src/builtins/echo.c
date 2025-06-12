/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:53:19 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/12 13:58:55 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Runs in child process - no issues with forking since 
it doesn’t change anything.

echo hello world
Output: hello world\n
echo -n hello
Output: hello (No Trailing newline)
No errors - always returns 0
*/
int	echo_builtin(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (args[1] && ft_strcmp(args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
