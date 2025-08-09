#include "../../include/minishell.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int	len;
	int	i;

	len = end - start;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int	words;
	int	start;
	int	end;
	int	idx;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	start = -1;
	end = 0;
	idx = 0;
	while (s[end])
	{
		if (s[end] != c && start < 0)
			start = end;
		else if ((s[end] == c || !s[end + 1]) && start >= 0)
		{
			result[idx++] = word_dup(s, start, (s[end] == c) ? end : end + 1);
			start = -1;
		}
		end++;
	}
	result[idx] = NULL;
	return (result);
}
