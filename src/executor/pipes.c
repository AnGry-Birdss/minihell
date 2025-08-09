#include "../../include/minishell.h"
#include "../../include/executor.h"


static int	launch_child(t_command *cmd, t_shell *shell, int in_fd, int out_fd, int *pipe_fds, int n_pipes)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		int i = 0;
		while (i < n_pipes)
		{
			if (pipe_fds[i] != in_fd && pipe_fds[i] != out_fd)
				close(pipe_fds[i]);
			i++;
		}
		if (in_fd != STDIN_FILENO) {
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO) {
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execute_commands(shell, cmd);
		exit(shell->exit_status);
	}
	return (pid);
}


int	setup_pipes(t_shell *shell, t_command *cmd)
{
	int pipe_fds[512];
	int n_pipes = 0;
	pid_t pids[256];
	int idx = 0;
	int status;
	t_command *cur = cmd;

	// Count number of commands
	int n_cmds = 0;
	t_command *tmp = cmd;
	while (tmp) { n_cmds++; tmp = tmp->next; }

	// Create all pipes in advance
	int i = 0;
	while (i < n_cmds - 1) {
		int fds[2];
		if (pipe(fds) == -1)
			return (ERROR);
		pipe_fds[n_pipes++] = fds[0];
		pipe_fds[n_pipes++] = fds[1];
		i++;
	}

	int pipe_idx = 0;
	i = 0;
	cur = cmd;
	while (i < n_cmds) {
		int this_in = (i == 0) ? STDIN_FILENO : pipe_fds[pipe_idx - 2];
		int this_out = (i == n_cmds - 1) ? STDOUT_FILENO : pipe_fds[pipe_idx + 1];
		pids[idx++] = launch_child(cur, shell, this_in, this_out, pipe_fds, n_pipes);
		cur = cur->next;
		pipe_idx += 2;
		i++;
	}
	// Parent closes all pipe fds
	i = 0;
	while (i < n_pipes) {
		close(pipe_fds[i]);
		i++;
	}
	while (idx-- > 0)
		waitpid(pids[idx], &status, 0);
	return (WEXITSTATUS(status));
}
