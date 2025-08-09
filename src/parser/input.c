#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	add_arg(t_command *cmd, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (cmd->args[i])
		i++;
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		return (ERROR);
	i = 0;
	while (cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = arg;
	free(cmd->args);
	cmd->args = new_args;
	return (SUCCESS);
}

static int	handle_pipe(t_command **cmd)
{
	t_command	*new_cmd;

	new_cmd = create_command();
	if (!new_cmd)
		return (ERROR);
	(*cmd)->next = new_cmd;
	*cmd = new_cmd;
	return (SUCCESS);
}

// t_command *parse_input(char *input, t_shell *shell)
// {
// 	t_command *head;
// 	t_command *current;
// 	char *word;
// 	int i;
// 
// 	head = create_command();
// 	if (!head)
// 		return (NULL);
// 	current = head;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '|')
// 		{
// 			if (handle_pipe(&current) == ERROR)
// 				return (NULL);
// 			i++;
// 		}
// 		else
// 		{
// 			word = parse_word(input, &i, shell);
// 			if (!word || add_arg(current, word) == ERROR)
// 				return (NULL);
// 		}
// 	}
// 	return (head);
// }
