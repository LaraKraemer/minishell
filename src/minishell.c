
# include "minishell.h"

char **cell_split_line(char *line)
{
	char **tokens;
	unsigned int position;
	size_t		bufsize;
	char *token;

	bufsize = BUFSIZ;
	tokens = malloc(bufsize * sizeof * tokens);
	if (!tokens) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

	position = 0;
	token = strtok(line, DEL);
	while(token != NULL)
	{
		tokens[position++] = token;
		if(position >= bufsize)
		{
			bufsize *= 2;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			 if (!tokens) {
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
		}
		token = strtok(NULL, DEL); 

	}
	tokens[position] = NULL;
	return tokens;
}


// REPL
// READ - Evaluate - Print/ Execute - Loop
int main(void)
{

	char *line;
	char cwd[BUFSIZ];
	print_banner();
	while (1)
	{
		// 1 - readline 
		line = readline("testshell>$ ");
		if (!line) {
			printf("EOF");
			break;
			}

		// add prompt history 
		if (*line)
			add_history(line);
		
		char **args = cell_split_line(line);
		int i = 0;
		while (args[i])
		{
			printf("Token[%d]: %s\n",i,  args[i]);
			i++;
		}
		// cd minimal testing
		cd_path(line, cwd, sizeof(cwd));
		printf("You typed: %s\n", line);

		// 2 - get tokens 
		// 		lexing -> parsing (EVALUATING)

		// 3 - Exec
		free(args);
		free(line);
	}
	return 0;
}