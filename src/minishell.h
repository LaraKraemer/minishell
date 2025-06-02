# ifndef MINISHELL_H
# define MINISHELL_H



# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h> 
# include <sys/types.h>
# include <dirent.h>
# include <readline/readline.h>


# define ERR_QUOTE "Syntax error: Unclosed quotes"
# define DEL  " \t\r\n\a"

char *cd_path(char *line, char *cwd, size_t cwd_size);
void print_banner(void);

#endif 