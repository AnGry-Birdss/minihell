/*
** minishell: include/parser.h
** Parser helper prototypes (norm: after struct definitions)
*/

#ifndef PARSER_H
# define PARSER_H


# include "minishell.h"

t_command   *create_command(void);
char        *parse_word(char *input, int *i, t_shell *shell);
t_command   *parse_input(char *input, t_shell *shell);

#endif
