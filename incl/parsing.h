/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:45:04 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/02 14:54:05 by dtimofee         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1
# define PIPE 2
# define REDIRECT_IN 3
# define REDIRECT_OUT 4
# define HEREDOC 5
# define APPEND 6

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token	*ms_lstnew(int type, char *value);
t_token	*ms_lstlast(t_token *lst);
void	ms_lstadd_back(t_token **lst, t_token *new);
void	skip_delimiter(char **s);

// typedef struct s_cmd
// {
// 	int		cmd_count;
// 	char	*cmd_path;
// 	char	**cmd_argv;
// }	t_cmd;

// typedef struct s_data
// {
// 	int		fd_in;
// 	int		fd_out;
// 	t_cmd	command;
// 	pid_t	*child_pid;
// 	int		*pipe_fd;
// 	char	**path_file;
// }	t_data;


#endif
