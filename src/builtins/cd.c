/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:18:43 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/23 17:08:08 by lkramer          ###   ########.fr       */
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

int	cd_builtin(t_command *cmd, char ***env)
{
	char	*target;
	char 	*oldpwd;
	
	 if (cmd->cmd_args && cmd->cmd_args[2])
        return (ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO), 1);
	if (cd_get_target_and_oldpwd(cmd, env, &target, &oldpwd))
        return (1);
    return (cd_change_and_update_env(target, oldpwd, env));
	
}

int	cd_get_target_and_oldpwd(t_command *cmd, char ***env, char **target, char **oldpwd)
{
    char cwd_before[PATH_MAX];

    if (!cmd || !cmd->cmd_args || !cmd->cmd_args[1] || !*cmd->cmd_args[1])
    {
        *target = get_env_value("HOME", *env);
        if (!*target)
            return (ft_putstr_fd(ERR_CD, STDERR_FILENO), 1);
    }
    else
        *target = cmd->cmd_args[1];
    if (!getcwd(cwd_before, sizeof(cwd_before)))
        return (perror("minishell: cd: getcwd"), 1);
    *oldpwd = ft_strdup(cwd_before);
    if (!*oldpwd)
        return (perror("minishell: cd: strdup"), 1);
    return (0);
}

int	cd_change_and_update_env(char *target, char *oldpwd, char ***env)
{
    char	cwd_after[PATH_MAX];
    char	*oldpwd_str;
    char	*pwd_str;

    if (chdir(target) == -1)
        return (ft_putstr_fd("minishell: cd: ", STDERR_FILENO), perror(target), free(oldpwd), 1);
    if (!getcwd(cwd_after, sizeof(cwd_after)))
        return (perror("minishell: cd: getcwd"), chdir(oldpwd), free(oldpwd), 1);
    oldpwd_str = ft_strjoin("OLDPWD=", oldpwd);
    pwd_str = ft_strjoin("PWD=", cwd_after);
    if (!oldpwd_str || !pwd_str)
        return (perror("minishell: cd: malloc"), free(oldpwd), free(oldpwd_str), free(pwd_str), 1);
    *env = assign_var_and_value(oldpwd_str + 6, oldpwd_str, *env);
    *env = assign_var_and_value(pwd_str + 3, pwd_str, *env);
    free(oldpwd_str);
    free(pwd_str);
    free(oldpwd);
    return (0);
}
