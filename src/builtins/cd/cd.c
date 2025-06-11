/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:43 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/02 17:17:30 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../incl/execution.h"


char *cd_path(char *line, char *cwd, size_t cwd_size)
{
	if (strcmp(line, "cd") == 0) {
			if (getcwd(cwd, cwd_size) != NULL)
				printf("%s\n", cwd);
			else
				perror("getcwd failed");
		}
	else if (strcmp(line, "cd ..") == 0){
		if (chdir("..") == 0) {
			if (getcwd(cwd, cwd_size) != NULL)
				printf("Moved to: %s\n", cwd);
			else
				perror("getcwd failed after cd ..");
		}
		else
			printf("chirdir failed");
		}
	else if (strcmp(line, "cd minishell") == 0){
		if (chdir("small_shell") == 0) {
			if (getcwd(cwd, cwd_size) != NULL)
				printf("Moved to: %s\n", cwd);
			else
				perror("getcwd failed after cd ..");
		}
		else
			printf("chirdir failed");
	}
	return (line);
}
