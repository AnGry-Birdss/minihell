#include "../../include/minishell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
	   if (ft_strchr(shell->env[i], '=')) {
		   ft_putstr_fd(shell->env[i], STDOUT_FILENO);
		   ft_putchar_fd('\n', STDOUT_FILENO);
	   }
		i++;
	}
	return (0);
}
