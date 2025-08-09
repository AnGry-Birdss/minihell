#include "../../include/minishell.h"
#include "../../include/utils.h"
#ifndef MAX_PATH
# define MAX_PATH 4096
#endif

static char	*get_home_dir(char **env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home)
		return (ft_strdup("/"));
	return (ft_strdup(home));
}

int	ft_cd(t_shell *shell, char **args)
{
	char	*path;
	char	cwd[MAX_PATH];

	if (!args[1])
	{
		path = get_home_dir(shell->env);
		if (!path)
			return (1);
	}
	else
		path = ft_strdup(args[1]);
	if (chdir(path) == -1)
	{
		print_error("cd", path, strerror(errno));
		free(path);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		set_env_var(shell, "PWD", cwd);
	   ft_putstr_fd(cwd, STDOUT_FILENO);
	   ft_putchar_fd('\n', STDOUT_FILENO);
	}
	free(path);
	return (0);
}
