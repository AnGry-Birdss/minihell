#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "minishell.h"

/* String utilities */
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);

/* Character utilities */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);

/* Memory utilities */
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);

/* Number utilities */
int			ft_atoi(const char *str);
char		*ft_itoa(int n);

/* Output utilities */
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		print_error(char *cmd, char *arg, char *msg);

/* Environment utilities */
char		*get_env_value(char **env, const char *key);
int			set_env_var(t_shell *shell, const char *key, const char *value);
int			unset_env_var(t_shell *shell, const char *key);

/* Input/Output utilities */
int			handle_heredoc(const char *delimiter);
int		is_valid_identifier(char *str);

#endif
