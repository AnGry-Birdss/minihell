#include "../../include/minishell.h"


static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (path);
}

static void	free_paths(char **paths)
{
	int	j;

	j = 0;
	while (paths && paths[j])
		free(paths[j++]);
	free(paths);
}

static char	*check_absolute_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	return (NULL);
}

static char	*search_paths(char **paths, char *cmd)
{
	int	k;
	char	*full_path;

	k = 0;
	while (paths[k])
	{
		full_path = join_path(paths[k], cmd);
		if (!full_path)
			return (NULL);
		if (!access(full_path, X_OK))
		{
			free_paths(paths);
			return (full_path);
		}
		free(full_path);
		k++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path_var;
	char	**paths;
	char	*result;

	result = check_absolute_path(cmd);
	if (result)
		return (result);
	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	result = search_paths(paths, cmd);
	if (!result)
		free_paths(paths);
	return (result);
}
