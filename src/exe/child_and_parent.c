/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:19:33 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/23 17:13:56 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/* 
Executes a pipeline of commands with fork/exec and pipe redirection 
*/
int	execute_with_pipex_logic(t_command *cmds, int cmd_count)
{
    int		*pipe_fds;
    pid_t	*child_pids;
    int		exit_status;
    int		i;

    pipe_fds = NULL;
	i = 0;
    child_pids = malloc(cmd_count * sizeof(pid_t));
    exit_status = 0;
    if (setup_pipes(cmd_count, &pipe_fds) == -1) 
		return (free(child_pids), 1);
    while (i < cmd_count)
    {
        child_pids[i] = fork();
        if (child_pids[i] == -1) 
			return (free(pipe_fds), free(child_pids), perror("fork"), exit(1), 1);
        if (child_pids[i] == 0)
            child_process(cmds, i, pipe_fds, cmds[i].env);
        else
            exit_status = parent_process(child_pids[i], pipe_fds, cmd_count, i);
        i++;
    }
    return (free(pipe_fds), free(child_pids), exit_status);
}

/* 
Initializes pipe file descriptors for command pipeline 
Allocates (cmd_count-1)*2 file descriptors in pipe_fds
*/
int setup_pipes(int cmd_count, int **pipe_fds)
{
    int i;

	i = 0;
    if (cmd_count <= 1)
        return (0);
    *pipe_fds = malloc((cmd_count - 1) * 2 * sizeof(int));
    if (!*pipe_fds)
        return (-1);
    while (i < cmd_count - 1)
    {
        if (pipe(*pipe_fds + i*2) == -1)
            return (-1);
        i++;
    }
    return (0);
}

/* 
Manages stdin/stdout redirection for a child process
*/
void setup_child_fds(int i, int *pipe_fds, int cmd_count)
{
    if (i > 0)
	{
        /* fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]); */
        if (dup2(pipe_fds[(i-1)*2], STDIN_FILENO) == -1)
            perror("dup2 input");
    }
    if (i < cmd_count - 1)
	{
        /* fprintf(stderr, "Connecting stdout to pipe %d\n", pipe_fds[i*2+1]); */
        if (dup2(pipe_fds[i*2+1], STDOUT_FILENO) == -1)
            perror("dup2 output");
    }
}

/* 
Manages file redirections and closes unused pipe ends
Closes all pipe FDs not used by this command and applies
file-based redirections when specified
*/
void handle_child_redirections(t_command *cmd, int i, int *pipe_fds, int cmd_count)
{
    int j;

    j = 0;
    while (j < (cmd_count - 1) * 2)
    {
        close(pipe_fds[j]);
        j++;
    }
    if (cmd[i].fd_in != STDIN_FILENO)
	{
		/* fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]); */
        dup2(cmd[i].fd_in, STDIN_FILENO);
        close(cmd[i].fd_in);
    }
    if (cmd[i].fd_out != STDOUT_FILENO)
	{
		/* fprintf(stderr, "Connecting stdout to pipe %d\n", pipe_fds[i*2+1]); */
        dup2(cmd[i].fd_out, STDOUT_FILENO);
        close(cmd[i].fd_out);
    }
}

/* 
Child process execution handler
Never returns - exits via exit() or execve()
*/
void child_process(t_command *cmds, int i, int *pipe_fds, char **envp)
{
    int cmd_count;

    if (cmds[i].fd_in < 0)
        cmds[i].fd_in = STDIN_FILENO;
    if (cmds[i].fd_out < 0)
        cmds[i].fd_out = STDOUT_FILENO;
    /* fprintf(stderr, "\n=== CHILD PROCESS DEBUG ===\n");
    fprintf(stderr, "Command index: %d\n", i);
    fprintf(stderr, "Command: %s\n", cmds[i].cmd); */
    cmd_count = 0;
    while (cmds[cmd_count].cmd)
        cmd_count++;
    setup_child_fds(i, pipe_fds, cmd_count);
    handle_child_redirections(cmds, i, pipe_fds, cmd_count);
	if (is_builtin(cmds[i].cmd_args[0]))
	{
		fprintf(stderr, "Executing builtin: %s\n", cmds[i].cmd_args[0]);
		exit(builtins(&cmds[i], &envp));
	}
    if (check_command(&cmds[i]) != 0)
        exit(cmds[i].exit_status);
	/* print_child_debug(cmds, i); */
	/* printf("\033[0;31mCommand %d path: %s\033[0m\n", i, cmds[i].cmd_path); */
    execve(cmds[i].cmd_path, cmds[i].cmd_args, envp);
    perror("execve");
    exit(127);
}

/* 
Manages parent process responsibilities during pipeline execution
Closes unused pipe ends and waits for child completion
*/
int parent_process(pid_t pid, int *pipe_fds, int cmd_count, int i)
{
    int status;
    
    if (i > 0)
        close(pipe_fds[2*(i-1)]);
    if (i < cmd_count-1)
        close(pipe_fds[2*i+1]);
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    if (WIFSIGNALED(status))
        return 128 + WTERMSIG(status);
    return (0);
}

/* Temporary debugging function */
/* void print_child_debug(t_command *cmd, int i)
{		   
    fprintf(stderr, "Executing: %s\n", cmd[i].cmd_path);
    fprintf(stderr, "With args: ");
	int k;
    k = 0;
    while (cmd[i].cmd_args[k])
    {
        fprintf(stderr, "'%s' ", cmd[i].cmd_args[k]);
        k++;
		if (cmd[i].cmd_args[k] == NULL)
			printf("NULL\n");
    }
    fprintf(stderr, "\n");
} */
