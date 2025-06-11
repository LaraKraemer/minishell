/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:49:58 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/11 11:39:58 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define ERR_QUOTE "Syntax minishell error: Unclosed quotes"
# define ERR_ENV "Not a valid identifier\n"
# define ERR_CD "testshell: cd: HOME not set\n"
# define ERR_ARG_SIZE "testshell: too many arguments\n"
# define DEL  " \t\r\n\a"

typedef struct s_cmd
{
	int		cmd_count;
	char	*cmd_path;
	char	**cmd_argv;
}	t_cmd;

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	t_cmd	command;
	pid_t	*child_pid;
	int		*pipe_fd;
	char	**path_file;
}	t_data;

// utils
int		ft_strcmp(const char *s1, const char *s2);
int		builtins(char **args, char **env);
void	print_banner(void);

// exit
int		exit_builtin(char **args);

// pwd 
int		pwd_builtin(char **args, char *cwd, size_t cwd_size);

// cd
int		cd_builtin(char *path);

// echo
int		echo_builtin(char **path);

// env
int		env_builtin(char **env);

// export 
int		export_builtin(char **args, char **env);
char	**assign_var(char **env, char *args);
char	**assign_var_and_value(char *equal_sign, char **env, char *args);
int		pdate_add_var(char **args, char **env);
int		export_without_var(char **env);

// export utils
int		valid_identifier(char *arg);
char	**copy_env(char **env);
void	sort_env(char **env);
void	print_export(char **env);
void	free_env(char **env);

// unset 
int		unset_builtin(char **args, char **env);
void	remove_var_from_env(char *args, char **env);

#endif
