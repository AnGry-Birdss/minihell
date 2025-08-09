#include "../../include/minishell.h"
#include "../../include/utils.h"

int	ft_unset(t_shell *shell, char **args)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_error("unset", args[i], "not a valid identifier");
			status = 1;
		}
		else
			unset_env_var(shell, args[i]);
		i++;
	}
	return (status);
}
