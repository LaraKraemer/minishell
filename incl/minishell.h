/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:02 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/03 18:55:30 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>
# include<readline/history.h>
# include "tokenisation.h"
# include "parsing.h"
# include "execution.h"
# include "builtins.h"
# include "Libft/libft.h"


void	print_banner(void);
void	free_resources(char *input, t_command *cmds, int count);
void	check_expansion(t_token *first_token, char **env, int exit_code);
/* static char	**copy_environment(char **envp);
 */


#endif
