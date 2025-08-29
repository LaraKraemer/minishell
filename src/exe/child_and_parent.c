/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:19:33 by dtimofee          #+#    #+#             */
/*   Updated: 2025/08/26 22:03:24 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/execution.h"

/*
Fork all children and close parent pipe ends
*/
int	fork_all_children(t_command *cmds, int cmd_count,
		int *pipe_fds, pid_t *child_pids)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		child_pids[i] = fork();
		if (child_pids[i] == -1)
			return (sys_error("fork", ERR_FORK), -1);
		if (child_pids[i] == 0)
			child_process(cmds, i, pipe_fds, cmds[i].env);
		else
		{
			if (i > 0)
				close(pipe_fds[2 * (i - 1)]);
			if (i < cmd_count - 1)
				close(pipe_fds[2 * i + 1]);
		}
		i++;
	}
	return (0);
}

/*
Wait for all children and get final exit status
*/
int	wait_all_children(pid_t *child_pids, int cmd_count)
{
	int	exit_status;
	int	status;
	int	i;

	exit_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		waitpid(child_pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_status);
}

/*
Executes a pipeline of commands with fork/exec and pipe redirection
*/
int	execute_with_pipex_logic(t_command *cmds, int cmd_count)
{
	int		*pipe_fds;
	pid_t	*child_pids;
	int		exit_status;

	pipe_fds = NULL;
	child_pids = malloc(cmd_count * sizeof(pid_t));
	if (setup_pipes(cmd_count, &pipe_fds) == -1)
		return (free(child_pids), 1);
	setup_parent_sigs();
	if (fork_all_children(cmds, cmd_count, pipe_fds, child_pids) == -1)
		return (free(pipe_fds), free(child_pids), exit(1), 1);
	exit_status = wait_all_children(child_pids, cmd_count);
	setup_interactive_sigs();
	return (free(pipe_fds), free(child_pids), exit_status);
}


/*
Manages file redirections and closes unused pipe ends
Closes all pipe FDs not used by this command and applies
file-based redirections when specified
*/
void	handle_child_redir(t_command *cmd, int i, int *pipe_fds, int cmd_count)
{
	int	j;

	j = 0;
	while (j < (cmd_count - 1) * 2)
	{
		close(pipe_fds[j]);
		j++;
	}
	if (cmd[i].fd_in != STDIN_FILENO)
	{
		dup2(cmd[i].fd_in, STDIN_FILENO);
		close(cmd[i].fd_in);
	}
	if (cmd[i].fd_out != STDOUT_FILENO)
	{
		dup2(cmd[i].fd_out, STDOUT_FILENO);
		close(cmd[i].fd_out);
	}
}

/*
Child process execution handler
Never returns - exits via exit() or execve()
*/
void	child_process(t_command *cmds, int i, int *pipe_fds, char **envp)
{
	int	cmd_count;
	int	check_status;

	if (cmds[i].fd_in == -1 || cmds[i].fd_out == -1)
		exit(1);
	setup_child_sigs();
	cmd_count = 0;
	while (cmds[cmd_count].cmd)
		cmd_count++;
	if (cmd_count > 1)
		setup_child_fds(i, pipe_fds, cmd_count);
	handle_child_redir(cmds, i, pipe_fds, cmd_count);
	if (is_builtin(cmds[i].cmd_args[0]))
		exit(builtins(&cmds[i], &envp));
	check_status = check_command(&cmds[i]);
	if (check_status != 0)
		exit(check_status);
	execve(cmds[i].cmd_path, cmds[i].cmd_args, envp);
	sys_error("execve", ERR_EXECVE);
	exit(127);
}


// child process debugging
/* fprintf(stderr, "\n=== CHILD PROCESS DEBUG ===\n");
    fprintf(stderr, "Command index: %d\n", i);
    fprintf(stderr, "Command: %s\n", cmds[i].cmd); */

// fprintf(stderr, "Executing builtin: %s\n", cmds[i].cmd_args[0]);

/* print_child_debug(cmds, i); */
// printf("\033[0;31mCommand %d path: %s\033[0m\n", i, cmds[i].cmd_path);

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

fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]);
fprintf(stderr, "Connecting stdin to pipe %d\n", pipe_fds[(i-1)*2]);
fprintf(stderr, "Connecting stdout to pipe %d\n", pipe_fds[i*2+1]);
} */
