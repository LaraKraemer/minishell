/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:50:02 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/03 16:09:45 by lkramer          ###   ########.fr       */
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
# include "tokenisation.h"
# include "parsing.h"
# include "execution.h"
# include "Libft/libft.h"


char **cell_split_input(char *input);


#endif
