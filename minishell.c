#include "minishell.h"

extern volatile sig_atomic_t f_sig;
// static int     exit_minishell(char **envp, char *p, int status, char *msg);

static int reset_std_in_out_err(t_data *data)
{
    if (dup2(data->fd0, STDIN_FILENO) == -1)
        return (perror(""), 1);
    if (dup2(data->fd1, STDOUT_FILENO) == -1)
        return (perror(""), 1);
    if (dup2(data->fd2, STDERR_FILENO) == -1)
        return (perror(""), 1);       
    return (0);
}

static void close_dup_fds(t_data *data)
{
    close(data->fd0);
    close(data->fd1);
    close(data->fd2);
}

int main(int ac, char **av, char **envp)
{
    t_data data;

	(void)av; // maybe we can remove these two from the argument since we don't use them, the problem is wether the envp will work or not;
	(void)ac; //
  //  __environ;
    ft_setup(&data, envp);
	while (!(data.exit) && !(data.is_a_pipe))
    {
        if (sigaction(SIGINT, &(data.SIG_INT), NULL) == -1) // remember to remove all the if condition on sigaction
            return (perror (""), errno);                    // check the man for possible errors
		if (sigaction(SIGQUIT, &(data.S_SIG_IGN), NULL) == -1)
            return (perror (""), errno);
        data.p_rdl = ft_read_line_gnl(1);
        if (signal_fun(-1))
        {
            data.status = 130;
            signal_fun(0);
        }
		if (!data.p_rdl) // C^d
        {
            if (isatty(STDIN_FILENO))
                ft_putstr("exit\n", 1);
			return (close_dup_fds(&data), config_malloc(NULL, 0), rl_clear_history(), data.status);
        }
        if (data.p_rdl[0])
            add_history(data.p_rdl);
        if (data.p_rdl[0] && check_syntax(&data))
            ;
        else if (data.p_rdl[0] && here_doc_fork(&(data.p_rdl), &(data.status), &data))
            return (close_dup_fds(&data), errno); // ?? free the other stuff ?
        else if (data.p_rdl && data.p_rdl[0])
        {
            if (found_pipe(data.p_rdl))
            {
                data.segments = c_split(data.p_rdl,'|');
                if (ft_pipes(&data))
                    return (close_dup_fds(&data), errno);
            }
            if (data.p_rdl)  // not great, this is done for when the piping is done so that the program wouldn't check for cmds;
                data.envp = parsing(&data);
            if (reset_std_in_out_err(&data)) // remember to close fd{0,1,2} 
                return (close_dup_fds(&data), config_malloc(NULL,0), 1);
        }
       // if (!data.is_a_pipe)
       // free(data.p_rdl); // we don't need this anymore since we dup and free the return of realdine.
       // config_malloc(NULL,0);
       // delete files of heredoc;
    }
    return(close_dup_fds(&data), rl_clear_history(), config_malloc(NULL,0), data.status);
}

// static int     exit_minishell(char **envp, char *p, int status, char *msg)
// {
//      free_all(envp);
//      free(p);
//      if (msg)
//         printf("%s",msg);
//      exit(status);
// }

// static int    set_default_fd(char *term_path)
// {
//     size_t  i = 0;
//     int     temp_fd = 0;

//     while (i < 3)
//     {
//         if (!isatty(i))
//         {
//             temp_fd = open(term_path, O_RDWR);
//             if (temp_fd < 0)
//                 return (perror("minishell: setting fd"), errno);
//             temp_fd = dup2(temp_fd, i);
//             if (temp_fd < 0)
//                 return (perror("minishell: setting fd"), errno);
//         }
//         i++;
//     }
//     return (0);
// }

// int main(int ac, char **av, char **envp)
// {
//     char    **segments;
// 	char *p = NULL;
//     char    *term = NULL;
// 	struct sigaction C_slash;
//     struct sigaction C_c;
// 	int	s_exit = 0;
//     int i = 0;

// 	(void)av;
// 	(void)ac;
// 	sigemptyset(&(C_slash.sa_mask));
//     sigemptyset(&(C_c.sa_mask));
//     C_slash.sa_flags = 0;
//     C_c.sa_flags = 0;
//     C_slash.sa_handler = SIG_IGN;
//     C_c.sa_handler = signal_handler;
// 	envp = ft_duplicate(envp);
//     term = ttyname(1);
//     if (!term)
//         {return (perror("minishell:"), free_all(envp), errno);}
// 	while (1 && !s_exit)
//     {
//        // printf("term_path: %s\n", term);
// 		sigaction(SIGQUIT, &C_slash, NULL);
//         sigaction(SIGINT, &C_c, NULL);
//         if (set_default_fd(term))
//             return (free_all(envp), errno);
// 		p = readline("minishell : ");
// 		if (!p)
//             exit_minishell(envp,p,0,"exit\n");
//         if (p[0])
//         {
//             i = found_pipe(p,envp);
//             if (i == 1)
//             {
//                 i = 0;
//                 segments = c_split(p, '|',envp);
//                 if (!segments)
//                     return(exit_minishell(envp,p,1,"failed malloc\n"));//protect malloc                    
//                 while(segments[i])
//                 {
//                     envp = parsing(&segments[i], envp, &s_exit);
//                     i++;    
//                 }
//                 free_all(segments);
//                 add_history(p);   
//             }
//             else if (i == 0)
//             {
//                 envp = parsing(&p, envp, &s_exit);
//                 add_history(p);
//             }
//             else
//                 return(exit_minishell(envp,p,1,"failed malloc\n"));//protect malloc
//         }
//         free(p);
//     }
//    	exit(s_exit); 
// }