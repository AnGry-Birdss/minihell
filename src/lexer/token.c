#include "../../include/minishell.h"

// Create a new token node
// Norm: max 25 lines, 4 params, 5 vars

t_token *token_new(t_token_type type, char *value)
{
	t_token *token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value ? ft_strdup(value) : NULL;
	token->next = NULL;
	return (token);
}

// Free a token list
void token_free(t_token *token)
{
	t_token *tmp;
	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
}
