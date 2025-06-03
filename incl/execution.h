/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:49:58 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/03 18:24:46 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define ERR_QUOTE "Syntminishellax error: Unclosed quotes"
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


void print_banner(void);
int exit_builtin(char *input);
int	ft_strcmp(const char *s1, const char *s2);

int builtins(char **args, char **env);
void pwd_builtin(char *cwd, size_t cwd_size);
char *cd_builtin(char *path, char *cwd, size_t cwd_size);
int echo_builtin(char **path);
int env_builtin(char **env);
int export_builtin(char **env);



#endif
