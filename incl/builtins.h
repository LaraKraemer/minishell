/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:49:58 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/03 14:15:42 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdlib.h>
# include <stdbool.h>
# include "minishell.h"
# include "parsing.h"
# define ERR_QUOTE "Syntax minishell error: Unclosed quotes"
# define ERR_ENV "Not a valid identifier\n"
# define ERR_CD "testshell: cd: HOME not set\n"
# define ERR_ARG_SIZE "testshell: too many arguments\n"
# define DEL  " \t\r\n\a"

/* typedef struct s_cmd
{
	int		cmd_count;
	char	*cmd_path;
	char	**cmd_argv;
}	t_cmd; */


// expansion
char	*get_env_value(char *arg, char **env);
char	*expand_exit_code(char *arg);

/*
builtins folder
*/
// utils.c
int		ft_strcmp(const char *s1, const char *s2);
int		builtins(t_command *cmd, char **env);
int		is_builtin(char *arg);
int		must_run_in_parent(const char *cmd);


// exit.c
int		exit_builtin(char **args);

// pwd.c
int		pwd_builtin(char **args, char *cwd, size_t cwd_size);

// cd.c
int	cd_builtin(t_command *cmd, char **env);
// echo.c
int		echo_builtin(t_command *cmd, char **env);
void	echo_env(char *arg, char **env);
void echo_exit_code(char *arg);

// env.c
int		env_builtin(char **env);

// export.c
int		export_builtin(char **args, char **env);
char	**assign_var(char **env, char *args);
char	**assign_var_and_value(char *equal_sign, char **env, char *args);
int		update_add_var(char **args, char **env);
int		export_without_var(char **env);

// export_utils.c
int		valid_identifier(char *arg);
void	sort_env(char **env);
void	print_export(char **env);
void	free_env(char **env);

// unset.c
int		unset_builtin(char **args, char **env);
void	remove_var_from_env(char *args, char **env);

#endif
