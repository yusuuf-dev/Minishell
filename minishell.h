/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 12:13:16 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 18:35:33 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 1
# define HEREDOC_MAX 16
# define PTR_TO_NULL 9
# define PIPE_FAILED "pipe function failed\n"
# define FORK_FAILED "fork function failed\n"
# define DUP_FAILED "dup function failed\n"
# define EXECVE_FAILED "execve function failed\n"
# define OPEN_FAILED "open function failed\n"
# define REDI_IN 0
# define REDI_OUT 1
# define REDI_APPEND 2
# define REDI_HEREDOC 3

typedef struct s_lstm
{
	void				*p;
	struct s_lstm		*next;
}						t_lstm;

typedef struct pipes
{
	int					i;
	pid_t				cpid;
	int					pipefd[2];
	int					old_pipe;
	char				**piped_cmds;
}						t_pipes;

typedef struct heredooc
{
	int					taken;
	char				*file_name;
	struct heredooc		*next;
}						t_heredoc;

typedef struct s_redi_lst
{
	char				*file_name;
	int					fd;
	int					redi_type;
	struct s_redi_lst	*next;
}						t_redi_lst;

/* remember that we reset the first PTR_TO_NULL num of pointers
	to NULL using memset */
/* DO NOT CHANGE THE ORDER OF THE FIRST PTR_TO_NULL pointers*/
typedef struct s_data
{
	char				*p_rdl;
	char				**rdl_args;
	char				**env_paths;
	char				**segments;
	char				*expand;
	char				*checker;
	t_heredoc			*heredooc;
	t_redi_lst			*redi_lst;
	char				*ptr_ambiguous;
	char				**envp;
	char				*cwd;
	char				**built_ins;
	unsigned char		status;
	int					exit;
	int					is_a_child;
	int					fd0;
	int					fd1;
	int					fd2;
	struct sigaction	s_sig_ign;
	struct sigaction	s_sig_dfl;
	struct sigaction	sig_int;
	struct sigaction	old_sig_quit;
	struct sigaction	old_sig_int;
}						t_data;

/*************************UTILS*********************************/
void					ft_strcpy(char *dest, char *src);
char					*ft_itoa(int n);
size_t					ft_strlen(char *s);
char					**ft_split(char *str, char c);
char					*ft_strdup(char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strchr(char *s, char c);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strldup(char *s, size_t n);
void					*ft_calloc(size_t n);
/***************************************************************/
/***************************BUILT-INS***************************/
int						ft_echo(char **p);
int						ft_pwd(t_data *data);
int						ft_cd(char **argv, char *argv_bkp, t_data *data,
							bool exists_in_cdpath);
char					**ft_new_export(t_data *data);
void					print_env(char **envp, int i, int j, int smallest);
int						ft_unset(t_data *data);
void					ft_env(t_data *data);
int						ft_exit(char **argv, t_data *data);
/***************************************************************/
/****************************SIGNALS*******************************/
void					signal_handler(int signum);
int						signal_fun(int n);
/***************************************************************/
/****************************HEREDOC****************************/
void					here_doc(t_data *data);
int						check_for_heredoc_create_node(t_data *data, size_t i,
							int found);
void					create_file_give_prompt(t_data *data, char *dl,
							int isquote, char *file_name);
void					create_t_heredoc_node(t_data *data);
int						update_heredoc_lst(char *s, t_data *data, int found,
							int i);
void					free_heredoc(t_data *data);
char					*heredoc_delimiter(char *s, int *isquote,
							int *index_ret);
/***************************************************************/
/****************************PIPE*******************************/
void					ft_pipes(t_data *data);
/***************************************************************/
/***************************REDICTIONS**************************/
void					redirections_parsing(t_data *data);
int						ft_redis_execute(t_data *data);
/***************************************************************/
void					*get_data(void *p);
int						c_strncmp(const char *s1, const char *s2);
void					parsing(t_data *data);
char					**ft_duplicate(char **s);
int						ft_isspace_to_space(char **s);
int						ft_isdigit(int c);
char					*ft_getenv(char *s, char **envp, unsigned char *status);
int						ft_check_spaces(char *s);
void					ft_putstr(char *s, int fd);
int						found_pipe(char *line);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						exit_atoi(char *s, long *rslt);
int						redi_atoi(char *nptr);
void					ft_setup(t_data *data);
///////////malloc
/***********************MALLOC**********************************/
/*config_malloc(NULL, 0, 0) free all execpt env stuff
config_malloc(NULL, 0, 1) free env only*/
/*config_malloc(NULL, 0, 2) free all ?*/
/*use it only when end program pass NULL to free all thing and exit;*/
/*to free all malloc except env use config_malloc(NULL,0, 0);*/
/*to free all malloc to end program by ctr+d or something else
 use config_malloc(NULL,2,2);*/
/*to free all env varriables call config_malloc(NULL,0,1);*/
void					*ft_malloc(size_t size);
void					*ft_malloc_env(size_t size);
void					config_malloc(void *ptr, int isfailed, int is_env);
void					free_ft_malloc(void *ptr, int is_envp);
/***************************************************************/
t_lstm					*head_of_ft_malloc_struct(t_lstm *head);
t_lstm					*envp_head_of_ft_malloc_struct(t_lstm *head);
char					*ft_strdup_env(char *s);
void					print_free_exit(char *s, int exit_code);
void					*ft_memset(void *ptr, int c, size_t n);
char					*ft_read_line_gnl(int p_prompt);
int						check_syntax(t_data *data);
char					*get_next_line(int fd);
char					*ft_substr_c(char *s, unsigned int start, size_t len);
char					**skip_quotes_split(char *str, char c);
void					custom_split(char *str, t_data *data, size_t i, char q);
char					*joinstr_helper(char *str, size_t i, size_t len,
							size_t index);
size_t					getlen_helper(char *str, size_t index);
int						validchar_helper(char c);
int						found_quotes(char *s);
int						ft_var_exists(char *s, char **envp);
char					**ft_duplicate_add_s(char **dup, char *s);
void					generate_checker(t_data *data, size_t is_exp);
char					*charjoin(char *s1, char c);
int						check_ambiguous(t_data *data);
int						found_redi(char c1, char c2);
void					add_linkedlist(t_data *data, t_redi_lst *new);
void					add_list_redi(t_data *data, int type, int fd,
							char *name);
int						valid_var(char *s);
void					close_dup_fds(void);
int						execute_command(char *path, t_data *data);

#endif