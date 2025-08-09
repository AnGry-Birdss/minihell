
#include "../../include/minishell.h"

static int is_valid_exit_arg(char *str)
{
	int i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int ft_exit(t_shell *shell, char **args)
{
	int	code;

	if (!shell->in_pipeline)
		ft_putstr_fd("exit\n", 1);
	if (!args[1])
	{
		shell->running = 0;
		return (shell->exit_status);
	}
	if (!is_valid_exit_arg(args[1]))
	{
		print_error("exit", args[1], "numeric argument required");
		shell->running = 0;
		return (255);
	}
	if (args[2])
	{
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	code = ft_atoi(args[1]);
	shell->running = 0;
	return (code & 255);
}
