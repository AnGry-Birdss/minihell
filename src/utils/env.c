/*
** minishell: src/utils/env.c
** User-implemented env functions (42 Norm, no forbidden stdlib)
*/

#include <stdlib.h>
#include "minishell.h"

// Return pointer to value for key in envp, or NULL if not found
char    *ft_getenv(const char *key, char **envp)
{
    size_t  klen;
    int     i;

    if (!key || !envp)
        return (NULL);
    klen = ft_strlen(key);
    i = 0;
    while (envp[i])
    {
        if (!ft_strncmp(envp[i], key, klen) && envp[i][klen] == '=')
            return (envp[i] + klen + 1);
        i++;
    }
    return (NULL);
}

// Duplicate envp (NULL-terminated array of strings)
char    **ft_envdup(char **envp)
{
    int     count;
    char    **copy;
    int     i;

    if (!envp)
        return (NULL);
    count = 0;
    while (envp[count])
        count++;
    copy = (char **)ft_calloc(count + 1, sizeof(char *));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < count)
    {
        copy[i] = ft_strdup(envp[i]);
        if (!copy[i])
        {
            while (i-- > 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[count] = NULL;
    return (copy);
}

// Free envp (NULL-terminated array of strings)
void    ft_envfree(char **envp)
{
    int i;

    if (!envp)
        return;
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

// Set or update key in envp (returns 0 on success, -1 on error)
int ft_setenv(char ***envp, const char *key, const char *value)
{
    int     i;
    size_t  klen;
    char    *newvar;

    if (!envp || !key || !value)
        return (-1);
    klen = ft_strlen(key);
    i = 0;
    while ((*envp)[i])
    {
        if (!ft_strncmp((*envp)[i], key, klen) && (*envp)[i][klen] == '=')
        {
            free((*envp)[i]);
            newvar = (char *)malloc(klen + ft_strlen(value) + 2);
            if (!newvar)
                return (-1);
            ft_strcpy(newvar, key);
            newvar[klen] = '=';
            ft_strcpy(newvar + klen + 1, value);
            (*envp)[i] = newvar;
            return (0);
        }
        i++;
    }
    // Add new variable
    {
        char    **newenv;
        int     count = 0;
        while ((*envp)[count])
            count++;
        newenv = (char **)ft_calloc(count + 2, sizeof(char *));
        if (!newenv)
            return (-1);
        i = 0;
        while (i < count)
        {
            newenv[i] = (*envp)[i];
            i++;
        }
        newvar = (char *)malloc(klen + ft_strlen(value) + 2);
        if (!newvar)
        {
            free(newenv);
            return (-1);
        }
        ft_strcpy(newvar, key);
        newvar[klen] = '=';
        ft_strcpy(newvar + klen + 1, value);
        newenv[count] = newvar;
        newenv[count + 1] = NULL;
        free(*envp);
        *envp = newenv;
    }
    return (0);
}

// Remove key from envp (returns 0 on success, -1 on error)
int ft_unsetenv(char ***envp, const char *key)
{
    int     i;
    int     j;
    size_t  klen;
    int     found;

    if (!envp || !key)
        return (-1);
    klen = ft_strlen(key);
    i = 0;
    found = 0;
    while ((*envp)[i])
    {
        if (!ft_strncmp((*envp)[i], key, klen) && (*envp)[i][klen] == '=')
        {
            free((*envp)[i]);
            found = 1;
            break;
        }
        i++;
    }
    if (!found)
        return (0);
    // Shift remaining
    j = i;
    while ((*envp)[j])
    {
        (*envp)[j] = (*envp)[j + 1];
        j++;
    }
    return (0);
}
