/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-06 13:14:07 by dtimofee          #+#    #+#             */
/*   Updated: 2025-09-06 13:14:07 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "tokenisation.h"
# include "parsing.h"

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
	int		redir_err_flag;
}	t_command;

typedef struct s_shell
{
	char		*input;
	char		*raw_input;
	t_token		*first_token;
	int			cmd_count;
	t_command	*cmds_array;
	int			exit_code;
	int			error_in_setup;
	int			i;
}	t_shell;

#endif
