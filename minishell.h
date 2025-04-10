#ifndef MINISHELL_H
#define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int     minishell(int ac, char **av);
char    **parsing(char *p, char **envp);
size_t	ft_strlen(char *s);
char	*ft_remove_isspace(char *s);
char	**ft_split(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s);
int	ft_strcmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(char *s, char c);

char	*ft_strjoinf(char *s1, char *s2);
char    *ft_strldup(char *s, size_t     n);

int	ft_echo(int argc,char	**p, char **envp);
int	ft_pwd(int argc,char	**argv, char **envp);
int	ft_cd(int argc, char **argv, char **envp);
char	**ft_export(int argc, char **argv, char **envp, int *status);

#endif
