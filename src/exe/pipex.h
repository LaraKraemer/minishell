/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:03:29 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/03 15:19:23 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include "Libft/libft.h"

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

int		set_path(t_data *data, char *envp[]);
int		check_command(t_data *data, char *command);
int		open_file(t_data *data, char *file, int i);
void	interprocess_communication(t_data *data, char *argv[], char *envp[]);
void	close_fds(t_data *data, int i);
void	create_pipe(t_data *data, int i);
void	free_array(char **str_array);
void	free_data(t_data *data);
void	cleanup_and_exit(t_data *data, int i, int err);

#endif
*/