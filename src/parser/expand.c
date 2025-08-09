#include "../../include/minishell.h"

static size_t	get_var_len(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*get_var_value(char *var, t_shell *shell)
{
	char	*value;

	if (var[0] == '?')
		return (ft_itoa(shell->exit_status));
	value = ft_getenv(var, shell->env);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*result;
	char	*var;
	char	*value;
	int		i;
	int		len;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			len = get_var_len(str + i + 1);
			var = ft_substr(str, i + 1, len);
			value = get_var_value(var, shell);
			result = ft_strjoin(result, value);
			free(var);
			free(value);
			i += len + 1;
		}
		else
			result = ft_strjoin(result, str + i++);
	}
	return (result);
}
