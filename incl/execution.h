/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:49:58 by lkramer           #+#    #+#             */
/*   Updated: 2025/06/02 17:50:08 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define ERR_QUOTE "Syntminishellax error: Unclosed quotes"
# define DEL  " \t\r\n\a"

char *cd_path(char *line, char *cwd, size_t cwd_size);
void print_banner(void);

#endif
