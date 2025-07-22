#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE     1
#define HEREDOC_MAX     16
#define PTR_TO_NULL     9
#define PIPE_FAILED     "pipe function failed\n"
#define FORK_FAILED     "fork function failed\n"
#define DUP_FAILED      "dup function failed\n"
#define EXECVE_FAILED   "execve function failed\n"
#define OPEN_FAILED     "open function failed\n"
#define REDI_IN         0
#define REDI_OUT        1
#define REDI_APPEND     2
#define REDI_HEREDOC    3
//#define INVALID_FD      -1
// for malloc garbage collector
typedef struct s_lstm
{
    void            *p;
    struct s_lstm   *next;
} t_lstm;

typedef struct pipes
{
    int     i;
    pid_t   cpid;
    int     pipefd[2];
    int     old_pipe;
    char    **piped_cmds;
  //  int     *is_a_pipe;
} pipes_t;


typedef struct heredooc
{
    int         arg_num; // wether the foundheredoc in the ft_all_redirection will use this node or not
    int         taken;  // wether will the readline use this node or not
    char        *file_name;
    struct heredooc   *next;
}t_heredoc;

typedef struct s_redi_lst
{
    char                *file_name;
    int                 fd;
    int                 redi_type;
    struct s_redi_lst   *next;
} t_redi_lst;

/* remember that we reset the first PTR_TO_NULL num of pointers
    to NULL using memset */
/* DO NOT CHANGE THE ORDER OF THE FIRST PTR_TO_NULL pointers*/
typedef struct s_data
{
    char              *p_rdl;
    char              **rdl_args;
    char              **env_paths;
    char              **segments;
    char              *expand;
    char              *checker;
    t_heredoc         *heredooc;
    t_redi_lst        *redi_lst;
    char              *ptr_ambiguous;
    char              **envp;
    unsigned char     status;
    int               exit;
    int               is_a_child;
    int               fd0, fd1, fd2;
    struct sigaction    S_SIG_IGN;
    struct sigaction    S_SIG_DFL;
    struct sigaction    SIG_INT;
    struct sigaction    OLD_SIG_QUIT;
    struct sigaction    OLD_SIG_INT;
}t_data;


/*************************UTILS*********************************/
void    ft_strcpy(char *dest, char *src);
char	*ft_itoa(int n);
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
/***************************************************************/
/***************************BUILT-INS***************************/
int     ft_echo(char **p);
int     ft_pwd(char	**argv, char **envp);
int     ft_cd(char **argv, char ***envp);
char	**ft_export(char **argv, char **envp, unsigned char *status);
char    **ft_new_export(t_data *data); // new export just to parse only data i didn't change original one because we call other place ft_export to chane vars
int		ft_unset(t_data *data);
//int     ft_env(char **argv, char **envp, char **envp_paths);
void    ft_env(t_data *data);
int     ft_exit(char **argv, unsigned char *status, int *s_exit);
/***************************************************************/
/****************************SIGNALS*******************************/
void    signal_handler(int signum);
int     signal_fun(int n);
/***************************************************************/
/****************************HEREDOC****************************/
void     here_doc(t_data *data);
int     check_for_heredoc_create_node(t_data *data, size_t i, int found);
void	create_file_give_prompt(t_data *data, char *dl, int isquote, char *file_name);
void    create_t_heredoc_node(t_data *data);
int     update_used_heredoc_list(char *s, t_data *data, int found, int i);
void    free_heredoc(t_data *data);
char    *heredoc_old_delimiter(char *s ,int *isquote, int *index_ret);
//int     found_heredoc(char *s);
char    *heredoc_delimiter(char *s ,int *isquote);
int     ft_isheredoc(char *p, char **envp, unsigned char *status);
/***************************************************************/
/****************************PIPE*******************************/
void     ft_pipes(t_data *data);
/***************************************************************/
/***************************REDICTIONS**************************/
int	    parse_redirection(t_data *data);
void    redirections_parsing(t_data *data);
int     ft_redis_execute(t_data *data);
/***************************************************************/
void    *get_data(void *p);
int     c_strncmp(const char *s1, const char *s2);
int     costum_atoi(char *s, unsigned char *status, int fd);
//int     minishell(int ac, char **av);
void	parsing(t_data *data);
//char	*ft_remove_isspace(char *s);
//char	**free_all(char **str);
char	**ft_duplicate(char	**s, size_t add_size);
int 	ft_isspace_to_space(char **s);
int     ft_isdigit(int c);
char	*ft_getenv(char *s, char **envp, unsigned char *status);
int		ft_check_spaces(char *s); // this function returns 1 if the argument contains only (isspace) chars.
void    ft_putstr(char *s, int fd);
char    *convert_env_var(char *s,char **envp);
//char	**c_split(char *str, char c, char **envp, unsigned char *status);
// char	**c_split(char *str, char c);
char    *rm_quotes(char *str);
int     found_q(char *s);
int     found_pipe(char *line);
char    *rm_quotes_expand(char *str, char **envp, unsigned char *status);
int	    ft_isalpha(int c);
int	    ft_isalnum(int c);
int	    c_atoi(char *s, long *rslt);
int     costum_atoi(char *nptr, unsigned char *status, int fd);
void    ft_setup(t_data *data, char **envp);
///////////malloc
void    *ft_malloc(size_t size);
void    *ft_malloc_env(size_t size);
void    config_malloc(void *ptr, int isfailed, int is_env);
t_lstm	*head_of_ft_malloc_struct(t_lstm *head);
t_lstm  *envp_head_of_ft_malloc_struct(t_lstm *head);
char    *ft_strdup_env(char *s);
void	free_ft_malloc(void *ptr, int is_envp);
void	print_free_exit(char *s, int exit_code);

// config_malloc(NULL, 0, 0) // free all execpt env stuff
// config_malloc(NULL, 0, 1) // free env only
// config_malloc(NULL, 0, 2) // free all ?
// use it only when end program pass NULL to free all thing and exit;
// to free all malloc except env use config_malloc(NULL,0, 0);
// to free all malloc to end program by ctr+d or something else use config_malloc(NULL,2,2);
// to free all env varriables call config_malloc(NULL,0,1);
void    config_rdline(char **p ,t_data *data);
void    *ft_memset(void *ptr, int c, size_t n);
char    *ft_read_line_gnl(int p_prompt);
int     check_syntax(t_data *data);
char	*get_next_line(int fd);
char	*ft_substr_c(char *s, unsigned int start, size_t len);
char	**c_split_02(char *str, char c, char **envp, unsigned char *func_status);
char    *expand(char *str, char **envp, unsigned char *status);
char	**c_split(char *str, char c);
void    custom_split(char *str, t_data *data, size_t i, char q);
char	*joinstr_helper(char *str, size_t i, size_t len, size_t index);
size_t	getlen_helper(char *str, size_t index);
int	    validchar_helper(char c);
int     found_quotes(char *s);

#endif