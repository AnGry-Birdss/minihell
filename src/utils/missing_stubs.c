/*
** minishell: src/utils/missing_stubs.c
** Norm-compliant stubs for missing functions to allow linking
*/

#include "../../include/minishell.h"
#include "../../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parser helpers
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
    return (cmd);
}

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

// Heredoc stub
int handle_heredoc(const char *delimiter)
{
    (void)delimiter;
    // Return a dummy fd (STDIN_FILENO)
    return (STDIN_FILENO);
}

// Print error stub
void print_error(char *cmd, char *arg, char *msg)
{
    if (cmd)
        fprintf(stderr, "%s: ", cmd);
    if (arg)
        fprintf(stderr, "%s: ", arg);
    if (msg)
        fprintf(stderr, "%s", msg);
    fprintf(stderr, "\n");
}

// Env helpers
char *get_env_value(char **env, const char *key)
{
    int     i = 0;
    size_t  klen = ft_strlen(key);
    if (!env || !key)
        return (NULL);
    while (env[i])
    {
        if (!ft_strncmp(env[i], key, klen) && env[i][klen] == '=')
            return (env[i] + klen + 1);
        i++;
    }
    return (NULL);
}

int set_env_var(t_shell *shell, const char *key, const char *value)
{
    (void)shell;
    (void)key;
    (void)value;
    return (0);
}

int unset_env_var(t_shell *shell, const char *key)
{
    (void)shell;
    (void)key;
    return (0);
}
