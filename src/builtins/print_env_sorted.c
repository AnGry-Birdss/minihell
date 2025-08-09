#include "../../include/minishell.h"
#include <stdlib.h>

static void swap(char **a, char **b)
{
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_env_sorted(char **env)
{
	int i, j, n;
	char **copy;

	// Count env size
	n = 0;
	while (env[n])
		n++;
	// Copy env
	copy = (char **)malloc(sizeof(char *) * (n + 1));
	if (!copy)
		return;
	for (i = 0; i < n; i++)
		copy[i] = env[i];
	copy[n] = NULL;
	// Simple bubble sort
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (ft_strcmp(copy[j], copy[j + 1]) > 0)
				swap(&copy[j], &copy[j + 1]);
	// Print
	for (i = 0; i < n; i++)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(copy[i], 1);
		ft_putchar_fd('\n', 1);
	}
	free(copy);
}
