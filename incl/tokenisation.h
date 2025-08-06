/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:49:14 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/25 11:49:42 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
// # include "minishell.h"
// # include "parsing.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_UNKNOWN
}	t_token_type;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

t_token			*ms_lstnew(int type, char *value);
t_token			*ms_lstlast(t_token *lst);
void			ms_lstadd_back(t_token **lst, t_token *new_node);
void			skip_delimiter(char **s);
int				correct_delimiter(int c);
int				special_character(int c);
int				is_word_token_start(int c);
char			*copy_words(char **start, char **envp, int last_exit_code);
int				get_tokens(char *input, t_token **first_token, char **envp, int last_exit_code);
t_token_type	determine_type(char *start, char *next);
char			*determine_value(t_token_type type, char **start, char **envp, int last_exit_code);
int				error_input(char *msg, int error);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strjoin_char(char *s, char c);

// expansion
char	*get_env_value(char *arg, char **env);
char	*expand_exit_code(char *arg, int exit_code);
char	*expand_variable(char *start, char **envp, int last_exit_code);

#endif
