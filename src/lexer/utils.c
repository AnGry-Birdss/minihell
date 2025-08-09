#include "../../include/minishell.h"

// Check if character is a shell metacharacter
int is_metachar(char c)
{
   return (c == '|' || c == '<' || c == '>' || c == ';');
}

// Identify token type from character
// Norm: max 25 lines, 4 params, 5 vars

t_token_type get_token_type(const char *s)
{
   if (!s)
	   return (TOKEN_EOF);
   if (s[0] == '|')
	   return (TOKEN_PIPE);
   if (s[0] == '<' && s[1] == '<')
	   return (TOKEN_REDIRECT_HEREDOC);
   if (s[0] == '>' && s[1] == '>')
	   return (TOKEN_REDIRECT_APPEND);
   if (s[0] == '<')
	   return (TOKEN_REDIRECT_IN);
   if (s[0] == '>')
	   return (TOKEN_REDIRECT_OUT);
   if (s[0] == ';')
	   return (TOKEN_SEMICOLON);
   return (TOKEN_WORD);
}
