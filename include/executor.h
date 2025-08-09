/*
** minishell: include/executor.h
** Executor function prototypes
*/

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void    execute_commands(t_shell *shell, t_command *cmd);
int     setup_pipes(t_shell *shell, t_command *cmd);
int     setup_redirections(t_command *cmd);

#endif
/*
** minishell: include/executor.h
** Executor function prototypes
*/

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

void    execute_commands(t_shell *shell, t_command *cmd);
int     setup_pipes(t_shell *shell, t_command *cmd);

#endif
