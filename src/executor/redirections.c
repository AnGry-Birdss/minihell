#include "../../include/minishell.h"
#include "../../include/utils.h"

static int	handle_input_redir(t_command *cmd)
{
	int	fd;

	if (cmd->heredoc_delim)
	{
		fd = handle_heredoc(cmd->heredoc_delim);
		if (fd == -1)
			return (ERROR);
	}
	else
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd == -1)
		{
			print_error(NULL, cmd->input_file, strerror(errno));
			return (ERROR);
		}
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	handle_output_redir(t_command *cmd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append_mode)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		print_error(NULL, cmd->output_file, strerror(errno));
		return (ERROR);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

int	setup_redirections(t_command *cmd)
{
	if (cmd->input_file)
		if (handle_input_redir(cmd) == ERROR)
			return (ERROR);
	if (cmd->output_file)
		if (handle_output_redir(cmd) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
