/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:19:33 by dtimofee          #+#    #+#             */
/*   Updated: 2025/07/08 21:41:35 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
1 input 
1 output 
1 command 
if file descriptor is filled write / read from it. 
do we have input / output redirections 		
	*/ 

int	execute_with_pipex_logic(t_command *cmds, int cmd_count, char **envp)
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
            child_process(cmds, i, pipe_fds, envp);
        else
            exit_status = parent_process(child_pids[i], pipe_fds, cmd_count, i);
        i++;
    }
    return (free(pipe_fds), free(child_pids), exit_status);
}

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

void setup_child_fds(int i, int *pipe_fds, int cmd_count)
{
    if (i > 0)
	{
        fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]);
        if (dup2(pipe_fds[(i-1)*2], STDIN_FILENO) == -1)
            perror("dup2 input");
    }
    if (i < cmd_count - 1)
	{
        fprintf(stderr, "Connecting stdout to pipe %d\n", pipe_fds[i*2+1]);
        if (dup2(pipe_fds[i*2+1], STDOUT_FILENO) == -1)
            perror("dup2 output");
    }
}

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
		fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]);
        dup2(cmd[i].fd_in, STDIN_FILENO);
        close(cmd[i].fd_in);
    }
    if (cmd[i].fd_out != STDOUT_FILENO)
	{
		fprintf(stderr, "Connecting stdout to pipe %d\n", pipe_fds[i*2+1]);
        dup2(cmd[i].fd_out, STDOUT_FILENO);
        close(cmd[i].fd_out);
    }
}

void child_process(t_command *cmds, int i, int *pipe_fds, char **envp)
{
    int cmd_count;

    if (cmds[i].fd_in < 0)
        cmds[i].fd_in = STDIN_FILENO;
    if (cmds[i].fd_out < 0)
        cmds[i].fd_out = STDOUT_FILENO;
    fprintf(stderr, "\n=== CHILD PROCESS DEBUG ===\n");
    fprintf(stderr, "Command index: %d\n", i);
    fprintf(stderr, "Command: %s\n", cmds[i].cmd);
    cmd_count = 0;
    while (cmds[cmd_count].cmd)
        cmd_count++;
    setup_child_fds(i, pipe_fds, cmd_count);
    handle_child_redirections(cmds, i, pipe_fds, cmd_count);
    if (check_command(&cmds[i]) != 0)
        exit(cmds[i].exit_status);
	print_child_debug(cmds, i);
	printf("\033[0;31mCommand %d path: %s\033[0m\n", i, cmds[i].cmd_path);
    execve(cmds[i].cmd_path, cmds[i].cmd_args, envp);
    perror("execve");
    exit(127);
}

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

void print_child_debug(t_command *cmd, int i)
{		   
    fprintf(stderr, "Executing: %s\n", cmd[i].cmd_path);
    fprintf(stderr, "With args: ");
	int k;
    k = 0;
    while (cmd[i].cmd_args[k])
    {
        fprintf(stderr, "'%s' ", cmd[i].cmd_args[k]);
        k++;
    }
    fprintf(stderr, "\n");
}





/* 

Later add to child process: 
 printf("\033[0;31mCommand %d path: %s\033[0m\n", i, cmds[i].cmd_path);
    if (is_builtin(cmds[i].cmd_args[0]))
    {
		fprintf(stderr, "Executing builtin: %s\n", cmds[i].cmd_args[0]);
        exit(builtins(&cmds[i], envp));
    }

	



void child_process(t_command *cmds, int i, int *pipe_fds, char **envp)
{
	if (cmds[i].fd_in < 0) cmds[i].fd_in = STDIN_FILENO;
    if (cmds[i].fd_out < 0) cmds[i].fd_out = STDOUT_FILENO;
	
	fprintf(stderr, "\n=== CHILD PROCESS DEBUG ===\n");
    fprintf(stderr, "Command index: %d\n", i);
    fprintf(stderr, "Command: %s\n", cmds[i].cmd);
    fprintf(stderr, "fd_in: %d, fd_out: %d\n", cmds[i].fd_in, cmds[i].fd_out);

    int cmd_count = 0;
    while (cmds[cmd_count].cmd != NULL)
        cmd_count++;
    if (i > 0)
    {
		fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]);
        if (dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO) == -1)
            perror("dup2 input");
    }
    if (i < cmd_count - 1)
    {
		 fprintf(stderr, "Connecting stdout to pipe %d\n", pipe_fds[i*2+1]);
        if (dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO) == -1)
            perror("dup2 output");
    }
	int j = 0;
    while (j < (cmd_count - 1) * 2)
	{
		close(pipe_fds[j]);
		j++;
	}
    if (cmds[i].fd_in != STDIN_FILENO)
    {
        if (dup2(cmds[i].fd_in, STDIN_FILENO) == -1)
            perror("dup2 fd_in");
		close(cmds->fd_in);
    }
    if (cmds[i].fd_out != STDOUT_FILENO)
    {
        if (dup2(cmds[i].fd_out, STDOUT_FILENO) == -1)
            perror("dup2 fd_out");
		 close(cmds->fd_out);
    }

	int actual_in = dup(STDIN_FILENO);
    int actual_out = dup(STDOUT_FILENO);
    fprintf(stderr, "ACTUAL FDs after dup2 - in:%d out:%d\n", actual_in, actual_out);
    close(actual_in);
    close(actual_out);
	
	if (check_command(&cmds[i]) != 0)
		exit(cmds[i].exit_status);
    fprintf(stderr, "Executing: %s\n", cmds[i].cmd_path);
    fprintf(stderr, "With args: ");
    for (int k = 0; cmds[i].cmd_args[k]; k++) {
        fprintf(stderr, "'%s' ", cmds[i].cmd_args[k]);
    }
    fprintf(stderr, "\n");
    for (int k = 0; cmds[i].cmd_args[k]; k++) {
        fprintf(stderr, "'%s' ", cmds[i].cmd_args[k]);
    }
    fprintf(stderr, "\n");
    execve(cmds[i].cmd_path, cmds[i].cmd_args, envp);
	perror("execve");
	exit(127);
    
}

static int parent_process(t_command *cmds, pid_t pid, int *pipe_fds, 
                         int cmd_count, int i)
{
    int status;
    
    if (i > 0) 
		close(pipe_fds[2*(i-1)]);
    if (i < cmd_count-1) 
		close(pipe_fds[2*i+1]);

    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status))
        cmds[i].exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        cmds[i].exit_status = 128 + WTERMSIG(status);
	return cmds[i].exit_status;
}

int	execute_with_pipex_logic(t_command *cmds, int cmd_count, char **envp)
{
	int exit_status = 0;
    int *pipe_fds = NULL;
	
    pid_t *child_pids = malloc(cmd_count * sizeof(pid_t));
    if (cmd_count > 1) {
        pipe_fds = malloc((cmd_count - 1) * 2 * sizeof(int));
		int i = 0;
        while (i < cmd_count - 1) {
            if (pipe(pipe_fds + i*2) == -1) {
                perror("pipe");
                exit(1);
            }
			i++;
        }
    }
	int i = 0;
    while (i < cmd_count)
	{
        child_pids[i] = fork();
        if (child_pids[i] == -1) {
            perror("fork");
            exit(1);
        }
        else if (child_pids[i] == 0) {
            child_process(cmds, i, pipe_fds, envp);
        }
        else {
            parent_process(cmds, child_pids[i], pipe_fds, cmd_count, i);
        }
		i++;
    }
    free(pipe_fds);
    free(child_pids);
	return exit_status;
} */


