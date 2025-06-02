# Minishell

> A simple Unix shell implemented in C as part of the 42 School curriculum.  
> This project replicates the basic behavior of Bash, including execution, redirection, piping, and built-in commands.
> This project is developed as a **team collaboration** by [Daria](https://github.com/tim-daria) and [Lara](https://github.com/LaraKraemer).

## Features

- Interactive prompt with history (readline)
- Built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections:
  - Input `<`, Output `>`, Append `>>`, Heredoc `<<`
- Pipes (`|`) between commands
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)
- Command execution with `PATH` resolution

---

## Compilation

```bash
make
```

## Usage 

```bash
./minishell

minishell$ echo Hello World
Hello World

minishell$ ls | grep .c > out.txt

minishell$ exit

```

## Resources

* [Write a shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
* [Minishell: Building a mini-bash](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
* [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
* [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
* [minishell- 42 docs](https://harm-smits.github.io/42docs/projects/minishell)
* [Video: Shell Program Explained ](https://www.youtube.com/watch?v=ubt-UjcQUYg)
* [Video: Shell Code-- More Detail ](https://www.youtube.com/watch?v=ZjzMdsTWF0U)