
#include "../../include/minishell.h"
#include "../../include/quote_utils.h"
#include "../../include/expand_utils.h"


// Minimal parser: split tokens at pipes, build t_command list
// Norm: max 25 lines, 4 params, 5 vars

t_command *parse_input(const char *input, t_shell *shell)
{
	(void)shell;
	t_token *tok = tokenize(input);
	t_command *head = NULL;
	t_command *tail = NULL;
	t_command *cmd;
	int argc, i;
	while (tok)
	{
		argc = 0;
		cmd = (t_command *)ft_calloc(1, sizeof(t_command));
		cmd->args = (char **)ft_calloc(64, sizeof(char *)); // max 63 args
		i = 0;
		while (tok && tok->type != TOKEN_PIPE && tok->type != TOKEN_SEMICOLON)
		{
			if (tok->type == TOKEN_WORD)
			{
				char *expanded = expand_vars_in_string(tok->value, shell->env, shell->exit_status);
				char *stripped = strip_quotes(expanded);
				free(expanded);
				if (stripped)
					cmd->args[i++] = stripped;
				else
					cmd->args[i++] = ft_strdup(tok->value);
				argc++;
			}
			else if (tok->type == TOKEN_REDIRECT_IN)
			{
				tok = tok->next;
				if (tok && tok->type == TOKEN_WORD)
				{
					char *stripped = strip_quotes(tok->value);
					char *expanded = NULL;
					if (stripped)
					{
						expanded = expand_vars_in_string(stripped, shell->env, shell->exit_status);
						free(stripped);
					}
					else
					{
						expanded = expand_vars_in_string(tok->value, shell->env, shell->exit_status);
					}
					if (expanded)
						cmd->input_file = expanded;
					else
						cmd->input_file = ft_strdup(tok->value);
				}
			}
			else if (tok->type == TOKEN_REDIRECT_OUT)
			{
				tok = tok->next;
				if (tok && tok->type == TOKEN_WORD)
				{
					char *stripped = strip_quotes(tok->value);
					char *expanded = NULL;
					if (stripped)
					{
						expanded = expand_vars_in_string(stripped, shell->env, shell->exit_status);
						free(stripped);
					}
					else
					{
						expanded = expand_vars_in_string(tok->value, shell->env, shell->exit_status);
					}
					if (expanded)
						cmd->output_file = expanded;
					else
						cmd->output_file = ft_strdup(tok->value);
					cmd->append_mode = 0;
				}
			}
			else if (tok->type == TOKEN_REDIRECT_APPEND)
			{
				tok = tok->next;
				if (tok && tok->type == TOKEN_WORD)
				{
					char *stripped = strip_quotes(tok->value);
					char *expanded = NULL;
					if (stripped)
					{
						expanded = expand_vars_in_string(stripped, shell->env, shell->exit_status);
						free(stripped);
					}
					else
					{
						expanded = expand_vars_in_string(tok->value, shell->env, shell->exit_status);
					}
					if (expanded)
						cmd->output_file = expanded;
					else
						cmd->output_file = ft_strdup(tok->value);
					cmd->append_mode = 1;
				}
			}
			else if (tok->type == TOKEN_REDIRECT_HEREDOC)
			{
				tok = tok->next;
				if (tok && tok->type == TOKEN_WORD)
				{
					char *stripped = strip_quotes(tok->value);
					char *expanded = NULL;
					if (stripped)
					{
						expanded = expand_vars_in_string(stripped, shell->env, shell->exit_status);
						free(stripped);
					}
					else
					{
						expanded = expand_vars_in_string(tok->value, shell->env, shell->exit_status);
					}
					if (expanded)
						cmd->heredoc_delim = expanded;
					else
						cmd->heredoc_delim = ft_strdup(tok->value);
				}
			}
			tok = tok->next;
		}
		cmd->args[i] = NULL;
		cmd->next = NULL;
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		if (tok && (tok->type == TOKEN_PIPE))
			tok = tok->next;
		if (tok && (tok->type == TOKEN_SEMICOLON))
			tok = tok->next;
	}
	token_free(tok);
	return (head);
}
