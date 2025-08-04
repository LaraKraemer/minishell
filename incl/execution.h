/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:37:27 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/04 17:27:09 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <stdbool.h>
# include "parsing.h"
# include "builtins.h"
# include "Libft/libft.h"


int		check_command(t_command *cmd_struct);
int		execute_with_pipex_logic(t_command *cmds, int cmd_count);
int setup_pipes(int cmd_count, int **pipe_fds);
int parent_process(pid_t pid, int *pipe_fds, int cmd_count, int i);
void handle_child_redirections(t_command *cmd, int i, int *pipe_fds, int cmd_count);
void print_child_debug(t_command *cmd, int i);
void setup_child_fds(int i, int *pipe_fds, int cmd_count);
/* static int parent_process(t_command *cmds, pid_t pid, int *pipe_fds,
                         int cmd_count, int i); */
void child_process(t_command *cmds, int i, int *pipe_fds, char **envp);
int		set_path(t_command *cmd, char *envp[]);
void	free_array(char **str_array);
void	free_commands(t_command *cmds, int cmd_count);

#endif
