/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:49:58 by lkramer           #+#    #+#             */
/*   Updated: 2025/08/21 15:14:43 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>
# include <stdbool.h>
# include "minishell.h"
# include "parsing.h"


// utils.c
int		ft_strcmp(const char *s1, const char *s2);
int		builtins(t_command *cmd, char ***global_env);
int		is_builtin(char *arg);
int		must_run_in_parent(const char *cmd);

// exit.c
int		exit_builtin(char **args);

// pwd.c
int		pwd_builtin(char *cwd, size_t cwd_size);

// cd.c
int		cd_builtin(t_command *cmd, char ***env);
int		cd_oldpwd(t_command *cmd, char ***env, char **target, char **oldpwd);
int		cd_change_and_update_env(char *target, char *oldpwd, char ***env);

// echo.c
int		echo_builtin(t_command *cmd);

// env.c
int		env_builtin(char **args, char **env);

// export.c
int		export_builtin(t_command *cmd, char ***global_env);
char	**assign_var(char *arg, char **env);
char	**assign_var_and_value(char *equal_sign, char *arg, char **env);
int		update_add_var(char **args, char ***global_env);
int		export_without_var(char **global_env);
char	**add_new_env_var(char *var, char ***env);

// export_utils.c
int		valid_identifier(char *arg);
void	sort_env(char **env);
void	print_export(char **env);
void	free_env(char **env);

// unset.c
int		unset_builtin(char **args, char **env);
void	remove_var_from_env(char *args, char **env);

#endif
