/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:43 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/03 14:34:42 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/builtins.h"

/* 
Runs in parent process - since it affects shell state

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
int	cd_builtin(t_command *cmd, char **env)
{
	char	*target;
	char    cwd_before[PATH_MAX];
    char    cwd_after[PATH_MAX];
	// char	cwd[PATH_MAX];
	if (!getcwd(cwd_before, sizeof(cwd_before))) {
        perror("minishell: cd: getcwd");
        return (1);
    }
	if (!cmd || !cmd->cmd_args || !cmd->cmd_args[1] || !*cmd->cmd_args[1])
	{
		target = get_env_value("HOME", env);
		if (!target)
		{
			ft_putstr_fd(ERR_CD, STDERR_FILENO);
			return (1);
		}
	}
	else
		target = cmd->cmd_args[1];
	if (chdir(target) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(target);
		return (1);
	}
	if (!getcwd(cwd_after, sizeof(cwd_after))) {
        perror("minishell: cd: getcwd");
        // Revert to previous directory if verification fails
        chdir(cwd_before);
        return (1);
    }
	printf("Changed directory from %s to %s\n", cwd_before, cwd_after);
	
	/* if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd: getcwd");
        return (1);
    } */
	return (0);
}

/*
 char *cwd, size_t cwd_size

 
int cd_env(char arg, char **env)
{
	
}


else 
	{
		target = cmd->cmd_args[1];
		if (!target)
		{
            target = get_env_value("HOME", env);
			if (!target)
			{
				ft_putstr_fd(ERR_CD, STDERR_FILENO);
				return (1);
			}
		}
	}
	char *oldpwd = getcwd(cwd, sizeof(cwd));
    if (!oldpwd) {
        perror("minishell: cd: getcwd");
        return (1);
    }
	if (chdir(target) == -1)
	{
		perror("cd failed");
		return (1);
	}
    if (getcwd(cwd, sizeof(cwd_size)))
	{
		update_add_var(cmd->cmd_args, env);
        get_env_value("PWD", env);
		
    } 
	else {
        perror("minishell: cd: getcwd");
        return (1);
    } 
		
*/
