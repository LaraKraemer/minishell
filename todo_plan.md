# To do's 

## Shell Loop & Basic User Input 

- [ ] display prompt
- [ ] read user input
- [ ] exit on Ctrl-D

# Lexical Analysis (Lexer)
 - [ ] Split input into tokens: words, redirection symbols, pipes
  - [ ] Handle:
  	- [ ] Whitespace
  	- [ ] Quotes (' and ")
  	- [ ] Pipes (|)
  	- [ ] Redirections (<, >, >>, <<)
  - [ ] Create a token struct and a token list
  - [ ] Implement error handling for invalid token sequences

## Parser 

- [ ] tokenezation 
- [ ] handle quotes
- [ ] prepare env var expansion

## Piping 

- [ ] handle multiple pipes
- [ ] connect fd between processes
- [ ] close unsused pipe end in parent/child
- [ ] use dup2 to redirect stdin/stdout 

## Redirections 

- [ ] Output redirection > 
- [ ] Input redirection <
- [ ] Append output redirection >>
- [ ] Heredoc redirection <<
	- [ ] stop reading at delimeter
	- [ ] Don't add heredoc input to history
- [ ] handle redirection errors (bad files, permissions)


## Builtins 

- [ ] implement echo
- [ ] implement cd
- [ ] implement pwd
- [ ] implement export
- [ ] implement unset
- [ ] implement env
- [ ] implement exit

## Basic Excecution

- [ ] run exceucutables via absolute / relative path
- [ ] run external commands fork + execve

## Signals 

- [ ] Implement Ctrl-C, Ctrl-



## Testing Edge Cases 

- [ ] test with different spaces
- [ ] test all built'ins individually
- [ ] test redirection with files
- [ ] test heredoc woth / without signal
- [ ] test pipe with external commands
- [ ] compare behaviour to bash
- [ ] use valgrind for memory leaks
- [ ] run 42 tester
