/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:37:27 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/05 17:58:07 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# ifndef O_DIRECTORY
#  define O_DIRECTORY 0200000
# endif

# include <stdlib.h>
# include <stdbool.h>
# include "parsing.h"
# include "builtins.h"
# include "libft/libft.h"

int		check_command(t_command *cmd_struct);
int		execute_with_pipex_logic(t_shell *sh);
int		setup_pipes(int cmd_count, int **pipe_fds);
int		wait_all_children(pid_t *child_pids, int cmd_count);
void	handle_child_redir(t_command *cmd, int i, int *pipe_fds, int cmd_count);
int		fork_all_children(t_shell *sh, int *pipe_fds, pid_t *child_pids);
void	setup_child_fds(int i, int *pipe_fds, int cmd_count);
void	child_process(t_shell *sh, int i, int *pipe_fds, pid_t *child_pids);
int		set_path(t_command *cmd, char *envp[]);
void	free_array(char **str_array);
void	free_commands(t_command *cmds, int cmd_count);
void	cleanup_and_exit(t_shell *sh, int *pipe_fds, pid_t *child_pids,
			int exit_code);

#endif
