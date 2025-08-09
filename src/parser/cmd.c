/*
** minishell: src/parser/cmd.c
** Minimal parser helpers for norm compliance
*/

#include "../../include/minishell.h"
#include "../../include/parser.h"

t_command   *create_command(void)
{
    t_command   *cmd;

    cmd = (t_command *)ft_calloc(1, sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->args = (char **)ft_calloc(1, sizeof(char *));
    if (!cmd->args)
    {
        free(cmd);
        return (NULL);
    }
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_mode = 0;
    cmd->heredoc_delim = NULL;
    cmd->next = NULL;
    return (cmd);
}

// Dummy parse_word: returns next word (space delimited) from input, advances i
char    *parse_word(char *input, int *i, t_shell *shell)
{
    int     start;
    int     len;
    char    *word;

    (void)shell;
    while (input[*i] == ' ')
        (*i)++;
    start = *i;
    while (input[*i] && input[*i] != ' ' && input[*i] != '|')
        (*i)++;
    len = *i - start;
    if (len <= 0)
        return (NULL);
    word = ft_substr(input, start, len);
    return (word);
}
