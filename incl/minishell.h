/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:02 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 13:43:42 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "tokenisation.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include "libft/libft.h"

// Error messages
# define ERR_QUOTE		"error: Unclosed quotes\n"
# define ERR_NUMERIC	"error: Numeric argument required\n"
# define ERR_ENV		"error: Not a valid identifier\n"
# define ERR_CD			"error: HOME not set\n"
# define ERR_ARG_SIZE	"error: Too many arguments\n"
# define EER_NO_FILE	"error: env: No such file or directory\n"
# define EER_ENV_NFOUND "error: env: Environment not found\n"
# define ERR_PATH		"error: PATH not set or found\n"
# define ERR_MEM_ALLO	"error: Memory allocation failed\n"
# define ERR_STR_DUP	"error: String duplication failed\n"
# define ERR_CMD_NFOUND	"error: Command not found\n"
# define ERR_PERMISSION "error: Permission denied\n"
# define ERR_SYNTAX_T	"Syntax Tokenizer\n"
# define ERR_SYNTAX_P	"Syntax Parser\n"
# define ERR_FILE_OPEN	"error: File open failed\n"
# define ERR_FORK		"error: Fork failed\n"
# define ERR_DUP2		"error: Dup2 output\n"
# define ERR_EXECVE		"error: Execve failed\n"
# define DEL			" \t\r\n\a"

// Colors for error messages
# define RESET		"\033[0m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"


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

/* Shell */
void	minishell_loop(t_shell *sh, char ***global_env);
void	init_shell(t_shell *sh);
int		read_trim_input(t_shell *sh);
int		tokenize_input(t_shell *sh, char **global_env);
int		parse_prepare_cmds(t_shell *sh, char **global_env);
int		execute_with_pipex_logic(t_command *cmds, int count);
int		setup_paths(t_shell *sh, char **global_env);
int		handle_builtins(t_shell *sh, char ***global_env);
void	execute_commands(t_shell *sh);

/* Utils */
void	print_banner(void);
void	free_resources(char *input, t_command *cmds, int count);
void	print_error(char *arg, char *message);
int		sys_error(char *context, char *arg);
int		print_error_return(char *arg, char *message, int code);

#endif
