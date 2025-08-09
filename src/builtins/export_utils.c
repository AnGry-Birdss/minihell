#include "../../include/minishell.h"

static void	free_split_result(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	ft_export_builtin(t_shell *shell, char **args)
{
	char	**key_value;
	int		i;
	int		status;

	if (!args[1])
	{
		print_env_sorted(shell->env);
		return (0);
	}
	status = 0;
	i = 1;
	while (args[i])
	{
		char *eq = ft_strchr(args[i], '=');
		int valid;
		if (eq)
		{
			int len = eq - args[i];
			char tmp = args[i][len];
			args[i][len] = '\0';
			valid = is_valid_identifier(args[i]);
			args[i][len] = tmp;
		}
		else
			valid = is_valid_identifier(args[i]);

		if (!valid)
		{
			print_error("export", args[i], "not a valid identifier");
			status = 1;
		}
		else if (eq)
		{
			key_value = ft_split(args[i], '=');
			if (key_value && key_value[0] && key_value[1])
				set_env_var(shell, key_value[0], key_value[1]);
			if (key_value)
				free_split_result(key_value);
		}
		i++;
	}
	if (status == 1)
		shell->exit_status = 1;
	return (status);
}
