/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:45:04 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/25 11:49:46 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include "tokenisation.h"

# define MAX_ARGS 100

typedef struct s_command
{
	char	*cmd;
	char	**cmd_args;
	char	**env;
	int		fd_in;
	int		fd_out;
	char	**path_file;
	char	*cmd_path;
	int		exit_code;
}	t_command;

int		count_cmd_num(t_token *first_token);
int		parse_input(t_command *cmds_array, t_token *first_token,
			int cmd_count, int exit_code, char **envp);
int		split_into_cmds(t_command *cmd, t_token **start,
			char **envp, int ex_code);
int		is_last_token_word(t_token *first_token);
int		in_out_redir(t_command *cmd, t_token **current_token,
			char **env, int ex_code);
int		open_file(t_command *cmd, char *file, int i);
int		init_array(t_command *cmds_array, int cmd_count, char **envp);
char	*quotes_token(char *token, char **envp, int exit_code);
char	**copy_env(char **env);


#endif
