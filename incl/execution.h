
# ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include "minishell.h"

# define ERR_QUOTE "Syntminishellax error: Unclosed quotes"
# define DEL  " \t\r\n\a"

char *cd_path(char *line, char *cwd, size_t cwd_size);
void print_banner(void);

#endif
