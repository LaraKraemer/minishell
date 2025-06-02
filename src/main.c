
# include "../incl/minishell.h"

char **cell_split_input(char *input)
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
	token = strtok(input, DEL);
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
int main(int argc, char **argv, char **env)
{

	char *input;
	char cwd[BUFSIZ];

	argv[argc] = "h";
	env[0] = "h";
	print_banner();
	while (1)
	{
		// 1 - readline
		input = readline("testshell>$ ");
		if (!input) {
			printf("EOF");
			break;
			}

		// add prompt history
		if (*input)
			add_history(input);

		char **args = cell_split_input(input);
		int i = 0;
		while (args[i])
		{
			printf("Token[%d]: %s\n",i,  args[i]);
			i++;
		}
		// get_tokens(input);
		// cd minimal testing
		cd_path(input, cwd, sizeof(cwd));
		printf("You typed: %s\n", input);

		// 2 - get tokens
		// 		lexing -> parsing (EVALUATING)

		// 3 - Exec
		free(args);
		free(input);
	}
	return 0;
}
