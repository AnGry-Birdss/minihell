#include "../../include/minishell.h"
#include "../../include/utils.h"
#ifndef MAX_PATH
# define MAX_PATH 4096
#endif

int	ft_pwd(void)
{
	char	cwd[MAX_PATH];

	if (!getcwd(cwd, sizeof(cwd)))
	{
		print_error("pwd", NULL, strerror(errno));
		return (1);
	}
   ft_putstr_fd(cwd, STDOUT_FILENO);
   ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
