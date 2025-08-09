/*
** minishell: src/utils/init_shell.c
** Minimal init_shell implementation for prompt and shell loop
*/

#include "../../include/minishell.h"

// Minimal shell initializer: duplicates env, sets defaults

t_shell *init_shell(char **envp)
{
	t_shell *shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
   shell->env = ft_envdup(envp);
   shell->exit_status = 0;
   shell->commands = NULL;
   shell->running = 1;
   shell->in_pipeline = 0;
	return (shell);
}
