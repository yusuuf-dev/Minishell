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

size_t	ft_strlen(char *s);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *s, char c);
char	*ft_strjoinf(char *s1, char *s2);
char    *ft_strldup(char *s, size_t     n);
int     minishell(int ac, char **av);
char    **parsing(char *p, char **envp, int *s_exit);
char	*ft_remove_isspace(char *s);

int     ft_echo(int argc,char	**p, char **envp);
int     ft_pwd(int argc,char	**argv, char **envp);
int     ft_cd(int argc, char **argv, char **envp);
char	**ft_export(int argc, char **argv, char **envp, int *status);
char	**ft_unset(int argc, char **argv, char **envp, int *status);
int     ft_env(int argc, char **argv, char **envp, char **envp_paths);
int     ft_exit(int argc, char **argv, char **envp);

char	**free_all(char **str);
char	**ft_duplicate(char **s);
char	*ft_isspace_to_space(char *s);
long	ft_atoi(char *s);
int     ft_isdigit(int c);
char	*ft_getenv(char *s, char **envp);


#endif
