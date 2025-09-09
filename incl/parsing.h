/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:45:04 by dtimofee          #+#    #+#             */
/*   Updated: 2025/09/07 14:23:19 by lkramer          ###   ########.fr       */
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
# include "shell.h"

# define MAX_ARGS 100

/*parsing*/
int		is_redirection_token(t_token *token);
int		is_last_token_word(t_token *first_token);
int		count_cmd_num(t_token *first_token);
int		parse_input(t_shell *sh);
int		split_into_cmds(t_command *cmd, t_shell *sh);
int		fill_cmd_struct(t_token **start, t_shell *sh, t_command *cmd);

/*redirections*/
int		handle_redirections(t_command *cmd, t_token **start, t_shell *sh);
int		in_out_redir(t_command *cmd, t_token **current_token,
			t_shell *sh);
int		handle_out_append(t_command *cmd, int current_type,
			char *expanded_file);
int		handle_in(t_command *cmd, int current_type,
			t_token **current_token, t_shell *sh);
int		check_for_heredocs(t_token **current_token, t_command *cmd,
			t_shell *sh);
int		open_file(t_command *cmd, char *file, int i);

int		init_array(t_command *cmds_array, int cmd_count, char **envp);
char	*quotes_token(char *token, char **envp, int exit_code);
char	**copy_env(char **env);
void	free_and_exit(t_shell *sh, char *temp, char *delimiter);

/*heredoc*/
int		handle_redir_heredoc(t_command *cmd, char *delimiter, t_shell *sh);
int		handle_heredoc(int *fd_in, char *delimiter, t_shell *sh);
int		check_quotes(char *delimiter);

#endif
