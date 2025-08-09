#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/quote_utils.h"
#include "../../include/utils.h"

// Remove only outermost matching quotes, preserve inner quotes
char *strip_quotes(const char *s)
{
	if (!s)
		return strdup("");
	int len = strlen(s);
	if (len >= 2 && ((s[0] == '"' && s[len-1] == '"') || (s[0] == '\'' && s[len-1] == '\''))) {
		char *out = malloc(len - 1);
		if (!out)
			return strdup("");
		memcpy(out, s + 1, len - 2);
		out[len - 2] = '\0';
		return out;
	}
	return strdup(s);
}

// Merge an array of tokens into a single string
char *merge_tokens(char **tokens, int count)
{
	if (count == 0) return NULL;
	char *result = strdup(tokens[0]);
	for (int i = 1; i < count; i++)
	{
		char *tmp = ft_strjoin(result, tokens[i]);
		free(result);
		result = tmp;
	}
	return result;
}
