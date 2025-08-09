/*
** minishell: src/executor/execute.c
** Minimal stub for execute_commands to resolve implicit declaration
*/

#include "../../include/executor.h"




static int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    if (ft_strcmp(cmd, "cd") == 0)
        return (2);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (3);
    if (ft_strcmp(cmd, "env") == 0)
        return (4);
    if (ft_strcmp(cmd, "exit") == 0)
        return (5);
    if (ft_strcmp(cmd, "unset") == 0)
        return (6);
    if (ft_strcmp(cmd, "export") == 0)
        return (7);
    return (0);
}

static int exec_builtin(t_shell *shell, t_command *cmd, int which)
{
    if (which == 1)
        return ft_echo(shell, cmd->args);
    if (which == 2)
        return ft_cd(shell, cmd->args);
    if (which == 3)
        return ft_pwd();
    if (which == 4)
        return ft_env(shell);
    if (which == 5)
        return ft_exit(shell, cmd->args);
    if (which == 6)
        return ft_unset(shell, cmd->args);
    if (which == 7)
        return 0; // stub for export
    return (1);
}

void    execute_commands(t_shell *shell, t_command *cmd)
{
    int builtin;
    pid_t pid;
    int status;
    int save_stdin = -1, save_stdout = -1;

    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    // Save original stdin/stdout
    save_stdin = dup(STDIN_FILENO);
    save_stdout = dup(STDOUT_FILENO);

    if (setup_redirections(cmd) == ERROR)
    {
        fprintf(stderr, "minishell: redirection error\n");
        // Restore before return
        if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
        if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
        if (save_stdin != -1) close(save_stdin);
        if (save_stdout != -1) close(save_stdout);
        shell->exit_status = 127;
        return;
    }

    if (cmd->next && (!shell->in_pipeline))
    {
        shell->in_pipeline = 1;
        shell->exit_status = setup_pipes(shell, cmd);
        shell->in_pipeline = 0;
        // Restore after pipeline
        if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
        if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
        if (save_stdin != -1) close(save_stdin);
        if (save_stdout != -1) close(save_stdout);
        return;
    }

    builtin = is_builtin(cmd->args[0]);
    if (builtin)
    {
        if (shell->in_pipeline || (cmd->next != NULL) || (shell->commands && shell->commands->next))
        {
            pid = fork();
            if (pid == 0)
            {
                int ret = exec_builtin(shell, cmd, builtin);
                fflush(stdout);
                // Restore before exit
                if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
                if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
                if (save_stdin != -1) close(save_stdin);
                if (save_stdout != -1) close(save_stdout);
                exit(ret);
            }
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                shell->exit_status = WEXITSTATUS(status);
            // Restore after child
            if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
            if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
            if (save_stdin != -1) close(save_stdin);
            if (save_stdout != -1) close(save_stdout);
            return;
        }
        shell->exit_status = exec_builtin(shell, cmd, builtin);
        // Restore after builtin
        if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
        if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
        if (save_stdin != -1) close(save_stdin);
        if (save_stdout != -1) close(save_stdout);
        return;
    }

    if (shell->in_pipeline)
    {
        fflush(stdout);
        execvp(cmd->args[0], cmd->args);
        perror("minishell");
        // Restore before exit
        if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
        if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
        if (save_stdin != -1) close(save_stdin);
        if (save_stdout != -1) close(save_stdout);
        exit(127);
    }
    pid = fork();
    if (pid == 0)
    {
        fflush(stdout);
        execvp(cmd->args[0], cmd->args);
        perror("minishell");
        // Restore before exit
        if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
        if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
        if (save_stdin != -1) close(save_stdin);
        if (save_stdout != -1) close(save_stdout);
        exit(127);
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    // Restore after external command
    if (save_stdin != -1) dup2(save_stdin, STDIN_FILENO);
    if (save_stdout != -1) dup2(save_stdout, STDOUT_FILENO);
    if (save_stdin != -1) close(save_stdin);
    if (save_stdout != -1) close(save_stdout);
}
