# Minishell — External Functions Reference

This document explains all the **external functions** allowed in the `minishell` project, based on the 42 school guidelines. These functions are grouped by category.

---

## Readline Library

| Function            | Description |
|---------------------|-------------|
| `readline(prompt)` | Reads a line of input from the user with a customizable prompt. Provides line editing and history. |
| `add_history(line)` | Adds a line to the readline history. |
| `rl_clear_history()`| Clears the entire history list. |
| `rl_on_new_line()`  | Prepares readline to display a new line prompt. |
| `rl_replace_line(text, clear_undo)` | Replaces the current line buffer with `text`. |
| `rl_redisplay()`    | Redisplays the prompt and line buffer. |

---

## Input/Output

| Function      | Description |
|---------------|-------------|
| `printf()`    | Formats and prints output to `stdout`. |
| `write(fd, buf, count)` | Writes `count` bytes from `buf` to file descriptor `fd`. |
| `read(fd, buf, count)`  | Reads `count` bytes into `buf` from file descriptor `fd`. |

---

## Memory Management

| Function      | Description |
|---------------|-------------|
| `malloc(size)`| Allocates `size` bytes of memory. |
| `free(ptr)`   | Frees previously allocated memory. |

---

## File and Directory Operations

| Function        | Description |
|-----------------|-------------|
| `open(path, flags, mode)` | Opens a file and returns a file descriptor. |
| `close(fd)`     | Closes an open file descriptor. |
| `access(path, mode)` | Checks file permissions (existence, read, write, execute). |
| `unlink(path)`  | Deletes a file. |
| `stat(path, buf)` | Gets file information. |
| `lstat(path, buf)` | Like `stat`, but for symlinks. |
| `fstat(fd, buf)` | Gets file info from a file descriptor. |
| `opendir(path)` | Opens a directory stream. |
| `readdir(dirp)` | Reads a directory entry from the stream. |
| `closedir(dirp)`| Closes the directory stream. |

---

## Process Management

| Function      | Description |
|---------------|-------------|
| `fork()`      | Creates a child process. Returns 0 to the child, PID to the parent. |
| `wait(status)`| Waits for a child process to finish. |
| `waitpid(pid, status, options)` | Waits for a specific child process. |
| `wait3(status, options, rusage)` | Like `waitpid` but returns resource usage. |
| `wait4(pid, status, options, rusage)` | Like `wait3` but waits for a specific PID. |
| `execve(path, argv, envp)` | Executes a new program, replacing the current process. |
| `exit(status)`| Terminates the process with a given status. |
| `kill(pid, sig)` | Sends a signal to a process. |

---

## Signal Handling

| Function         | Description |
|------------------|-------------|
| `signal(sig, handler)` | Sets a signal handler for `sig`. |
| `sigaction(sig, act, oldact)` | More advanced way to set signal handlers. |
| `sigemptyset(set)` | Initializes a signal set to empty. |
| `sigaddset(set, sig)` | Adds a signal to a signal set. |

---

## File Descriptor Manipulation

| Function   | Description |
|------------|-------------|
| `dup(fd)`  | Duplicates a file descriptor. |
| `dup2(fd, fd2)` | Duplicates `fd` to `fd2`, closing `fd2` if necessary. |
| `pipe(fd[2])` | Creates a pipe, writing end `fd[1]`, reading end `fd[0]`. |

---

## Working Directory

| Function        | Description |
|-----------------|-------------|
| `getcwd(buf, size)` | Gets the current working directory. |
| `chdir(path)`   | Changes the current working directory. |

---

## Error Handling

| Function     | Description |
|--------------|-------------|
| `strerror(errnum)` | Returns the error message string for `errnum`. |
| `perror(msg)` | Prints an error message for the last `errno` value. |

---

## Terminal & TTY

| Function         | Description |
|------------------|-------------|
| `isatty(fd)`     | Returns true if `fd` is a terminal. |
| `ttyname(fd)`    | Returns the terminal name associated with `fd`. |
| `ttyslot()`      | Returns the slot number for the current terminal. |
| `ioctl(fd, request, ...)` | Performs device-specific I/O control operations. |

---

## Environment

| Function     | Description |
|--------------|-------------|
| `getenv(name)` | Gets the value of an environment variable. |

---

## Termcap (Terminal Capabilities)

| Function         | Description |
|------------------|-------------|
| `tgetent(buf, termname)` | Loads the terminal entry into `buf` for `termname`. |
| `tgetflag(id)`   | Gets a boolean capability (true/false). |
| `tgetnum(id)`    | Gets a numeric capability. |
| `tgetstr(id, area)` | Gets a string capability. |
| `tgoto(cm, col, row)` | Computes cursor motion string. |
| `tputs(str, affcnt, putc_fn)` | Outputs the terminal string. |

---

## Notes

- Some functions (e.g., `rl_*`, `tget*`) require linking against **`-lreadline`** and/or **`-ltermcap`**.
- Functions like `fork`, `execve`, `dup2`, and `pipe` are fundamental to shell behavior.

---

## Good to know

Use `man <function>` in the terminal for full details, examples, and options.

```bash
man execve
man readline
man tcgetattr
