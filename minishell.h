#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct data
{
    char    *rdline;
    char    **rdl_args;
    char    **envp;
    char    **env_paths;
} t_data;

size_t	ft_strlen(char *s);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *s, char c);
char	*ft_strjoinf(char *s1, char *s2);
char    *ft_strldup(char *s, size_t     n);
void    *ft_calloc(size_t n);

int     minishell(int ac, char **av);
char	**parsing(char **p, char **envp, int *s_exit, int *status);
//char	*ft_remove_isspace(char *s);

int     ft_echo(char **p, char **envp);
int     ft_pwd(char	**argv, char **envp);
int     ft_cd(char **argv, char ***envp);
char	**ft_export(char **argv, char **envp, int *status);
char	**ft_unset(char **argv, char **envp, int *status);
int     ft_env(char **argv, char **envp, char **envp_paths);
int     ft_exit(char **argv, char **envp);

char	**free_all(char **str);
char	**ft_duplicate(char	**s, size_t add_size);
int 	ft_isspace_to_space(char **s);
int     ft_isdigit(int c);
char	*ft_getenv(char *s, char **envp);
int		ft_check_spaces(char *s); // this function returns 1 if the argument contains only (isspace) chars.
void    ft_putstr(char *s, int fd);
char    *convert_env_var(char *s,char **envp);
char	**c_split(char *str, char c, char **envp);
int     found_heredoc(char *s);
char    *rm_quotes(char *str);
int     found_q(char *s);
int     found_pipe(char *line);
int     ft_isheredoc(char *p, char **envp);
char    *rm_quotes_expand(char *str, char **envp);
char    *heredoc_delimiter(char *s ,int *isquote);
int	    ft_isalpha(int c);
int	    ft_isalnum(int c);
int	    c_atoi(char *s, long *rslt);
int	    parse_redirection(char **full_str, int *status, char **envp);
int     costum_atoi(char *nptr, int *status, int fd);
int     ft_pipes(char **piped_cmds, char **p, int *status, int *is_a_pipe);

#endif
