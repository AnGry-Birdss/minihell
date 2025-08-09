/*
** Main minishell file - shell loop and initialization
** Follows 42 Norm: max 25 lines per function, no ternary operators
*/

#include "minishell.h"
#include "parser.h"
#include "executor.h"

int	g_signal_received = 0;

static void	shell_cleanup(t_shell *shell)
{
	if (shell)
	{
		// Free all resources (implement as needed)
		// free_shell(shell);
	}
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	shell->running = 1;
	while (shell->running)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (input[0] != '\0')
			add_history(input);
	   t_command *cmd = parse_input(input, shell);
	   t_command *seg = cmd;
	   t_command *group_start;
	   t_command *group_end;
	   while (seg)
	   {
		   group_start = seg;
		   group_end = seg;
		   // Find the end of this group (until next semicolon or end)
		   while (group_end->next && group_end->next->args && group_end->next->args[0])
		   {
			   group_end = group_end->next;
		   }
		   t_command *next_group = group_end->next;
		   group_end->next = NULL;
		   shell->commands = group_start;
		   execute_commands(shell, group_start);
		   shell->commands = NULL;
		   group_end->next = next_group;
		   seg = next_group;
	   }
		free(input);
		// TODO: free cmd list
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	(void)envp;
// Initialize shell struct and env
	shell = init_shell(envp);
	if (!shell)
		return (1);
	shell_loop(shell);
	shell_cleanup(shell);
	return (0);
}
