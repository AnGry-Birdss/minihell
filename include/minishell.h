// Lexer utility
int is_metachar(char c);
char	*get_env_value(char **env, const char *key);
#ifndef MINISHELL_H
# define MINISHELL_H

# define ERROR   -1
# define SUCCESS  0
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>

typedef enum e_token_type
{
   TOKEN_WORD,
   TOKEN_PIPE,
   TOKEN_REDIRECT_IN,
   TOKEN_REDIRECT_OUT,
   TOKEN_REDIRECT_APPEND,
   TOKEN_REDIRECT_HEREDOC,
   TOKEN_SEMICOLON,
   TOKEN_EOF
} t_token_type;

// Token type helper
t_token_type get_token_type(const char *s);


typedef struct s_token {
	t_token_type    type;
	char            *value;
	struct s_token  *next;
} t_token;

// Token list helpers
t_token *token_new(t_token_type type, char *value);

// Lexer prototypes (must be after t_token definition)
t_token *tokenize(const char *input);
void token_free(t_token *token);

typedef struct s_command {
	char            **args;
	char            *input_file;
	char            *output_file;
	int             append_mode;
	char            *heredoc_delim;
	struct s_command *next;
} t_command;

typedef struct s_shell {
	char        **env;
	int         exit_status;
	t_command   *commands;
	int         running;
	int         in_pipeline; // flag to prevent recursive setup_pipes
} t_shell;

// Builtin prototypes (after all struct definitions)
int ft_echo(t_shell *shell, char **args);
int ft_cd(t_shell *shell, char **args);
int ft_pwd(void);
int ft_env(t_shell *shell);
int ft_exit(t_shell *shell, char **args);
int ft_unset(t_shell *shell, char **args);
int ft_export_builtin(t_shell *shell, char **args);
void print_env_sorted(char **env);
int is_valid_identifier(char *str);
int set_env_var(t_shell *shell, const char *key, const char *value);

// Function prototypes organized by module: lexer, parser, executor, builtins, utils

// String/memory utils (no <string.h> allowed)
char        *ft_strdup(const char *s);
size_t      ft_strlen(const char *s);
char        *ft_strcpy(char *dst, const char *src);
char        *ft_strcat(char *dst, const char *src);
char        *ft_strncat(char *dst, const char *src, size_t n);
size_t      ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t      ft_strlcat(char *dst, const char *src, size_t dstsize);
char        *ft_strjoin(const char *s1, const char *s2);
char        *ft_substr(const char *s, unsigned int start, size_t len);
int         ft_strcmp(const char *s1, const char *s2);
int         ft_strncmp(const char *s1, const char *s2, size_t n);
char        *ft_strchr(const char *s, int c);
void        *ft_memset(void *b, int c, size_t len);
void        *ft_memcpy(void *dst, const void *src, size_t n);
void        *ft_memmove(void *dst, const void *src, size_t len);
int         ft_memcmp(const void *s1, const void *s2, size_t n);
void        *ft_memchr(const void *s, int c, size_t n);
void        ft_bzero(void *s, size_t n);
void        *ft_calloc(size_t count, size_t size);

// Env utils
char        *ft_getenv(const char *key, char **envp);
char        **ft_envdup(char **envp);
void        ft_envfree(char **envp);
int         ft_setenv(char ***envp, const char *key, const char *value);
int         ft_unsetenv(char ***envp, const char *key);

// Other utils
char        **ft_split(const char *s, char c);
int         ft_isalnum(int c);
int         ft_isalpha(int c);
int         ft_isdigit(int c);
int         ft_atoi(const char *str);
char        *ft_itoa(int n);
void        ft_putchar_fd(char c, int fd);
void        ft_putstr_fd(char *s, int fd);
void        ft_putendl_fd(char *s, int fd);
void        print_error(char *cmd, char *arg, char *msg);

// Shell init
t_shell     *init_shell(char **envp);

#endif