#include "../../include/minishell.h"
#include "../../include/expand_utils.h"
#include "../../include/quote_utils.h"

int	ft_echo(t_shell *shell, char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		char *expanded = expand_vars_in_string(args[i], shell->env, shell->exit_status);
		char *stripped = strip_quotes(expanded);
		free(expanded);
		if (stripped && stripped[0] != '\0')
			ft_putstr_fd(stripped, STDOUT_FILENO);
		free(stripped);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
