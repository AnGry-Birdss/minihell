#include "../../include/minishell.h"
#include <stdio.h>

// Helper: skip whitespace
static int skip_ws(const char *s, int i)
{
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

// Helper: extract word, merging adjacent quoted/unquoted substrings, stripping quotes
#include "../../include/quote_utils.h"
static int extract_word(const char *s, int i, char **out)
{
	char *parts[64];
	int partc = 0;
	int start, len;
	char quote;
	while (s[i] && !(s[i] == ' ' || s[i] == '\t' || is_metachar(s[i]))) {
		quote = 0;
		if (s[i] == '\'' || s[i] == '"') {
			quote = s[i++];
			start = i;
			while (s[i] && s[i] != quote)
				i++;
			len = i - start;
			char *tmp = ft_substr(s, start, len);
			parts[partc++] = tmp;
			if (s[i] == quote)
				i++;
		} else {
			start = i;
			while (s[i] && s[i] != '\'' && s[i] != '"' && !(s[i] == ' ' || s[i] == '\t' || is_metachar(s[i])))
				i++;
			len = i - start;
			char *tmp = ft_substr(s, start, len);
			parts[partc++] = tmp;
		}
	}
	*out = merge_tokens(parts, partc);
	for (int j = 0; j < partc; j++)
		free(parts[j]);
	return i;
}

// Tokenizer core: split input into tokens, handle quotes, identify types
// Norm: max 25 lines, 4 params, 5 vars

t_token *tokenize(const char *input)
{
	int i = 0;
	t_token *head = NULL;
	t_token *tail = NULL;
	char *word;
	t_token *new_token;

	while (input[i])
	{
		i = skip_ws(input, i);
		if (!input[i])
			break;
		if (is_metachar(input[i]))
		{
			if ((input[i] == '<' || input[i] == '>') && input[i+1] == input[i])
			{
				new_token = token_new(get_token_type(&input[i]), ft_substr(input, i, 2));
				i += 2;
			}
			else
			{
				new_token = token_new(get_token_type(&input[i]), ft_substr(input, i, 1));
				i++;
			}
		}
		else
		{
			i = extract_word(input, i, &word);
			new_token = token_new(TOKEN_WORD, word);
			free(word);
		}
		if (!head)
			head = new_token;
		else
			tail->next = new_token;
		tail = new_token;
	}
	return (head);
}
