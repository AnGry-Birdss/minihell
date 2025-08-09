
#include "../../include/minishell.h"

// Norm-compliant export builtin wrapper
// Delegates to the real export logic in export_utils.c
int ft_export(t_shell *shell, char **args)
{
	return (ft_export_builtin(shell, args));
}
