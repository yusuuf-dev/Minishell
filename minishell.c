#include "minishell.h"

extern volatile sig_atomic_t f_sig;
static int     exit_minishell(char **envp, char *p, int status, char *msg);

//volatile sig_atomic_t child_exists = 0;

static int assign_std_in_out_err(t_data *data)
{
    data->fd0 = dup(0);
    if (data->fd0 == -1)
        return (perror(""), 1);
    data->fd1 = dup(1);
    if (data->fd1 == -1)
        return (perror(""), 1);
    data->fd2 = dup(2);
    if (data->fd2 == -1)
        return (perror(""), 1);
    return (0);
}

static int reset_std_in_out_err(t_data *data)
{
    if (dup2(data->fd0, 0) == -1)
        return (perror(""), 1);
    if (dup2(data->fd1, 1) == -1)
        return (perror(""), 1);
    if (dup2(data->fd2, 2) == -1)
        return (perror(""), 1);       
    return (0);
}

int main(int ac, char **av, char **envp)
{
    t_data data;

	(void)av; // maybe we can remove these two from the argument since we don't use them, the problem is wether the envp will work or not;
	(void)ac; //
  //  __environ;
    ft_setup(&data, envp);
    if (assign_std_in_out_err(&data))
        {return (free_all(envp), errno);}
	while (!(data.exit) && !(data.is_a_pipe))
    {
		sigaction(SIGQUIT, &(data.C_slash), NULL);
        sigaction(SIGINT, &(data.C_c), NULL);
        if (isatty(STDIN_FILENO))
		    data.p_rdl = readline("minishell : ");
	    else
	    {
		    char *line;
		    line = get_next_line(STDIN_FILENO);
            if (line && line[ft_strlen(line) - 1] == '\n')
                line[ft_strlen(line) - 1] = 0;
		    data.p_rdl = line;
	    }
        if (f_sig)
        {
            data.status = 130;
            f_sig = 0; // could this cause a data race ? , what if we sent SIGINT just as the proram was about to change the f_sig value ? I'm guessing it should work 
        }               // fine since I used an atomic var 
		if (!data.p_rdl) // C^d
        {
            if (isatty(STDIN_FILENO))
                ft_putstr("exit\n", 1);
			return (free_all(data.envp), free(data.p_rdl), rl_clear_history(), free_heredoc(&data, 1), data.status);
        }
        if (data.p_rdl[0])
            add_history(data.p_rdl);
        if (data.p_rdl[0] && check_syntax(data.p_rdl))
            data.status = 2;
        else if (data.p_rdl[0] && here_doc_fork(&(data.p_rdl), &(data.status), &data))
            return (errno);
        else if (data.p_rdl && data.p_rdl[0])
        {
            if (found_pipe(data.p_rdl))
            {
                data.segments = c_split(data.p_rdl, '|', data.envp, &(data.status));
                if (!data.segments)
                    return(exit_minishell(data.envp, data.p_rdl, 1, "failed malloc\n"));//protect malloc
                if (ft_pipes(&data))
                    return (errno);
            }
            if (data.p_rdl)  // not great, this is done for when the piping is done so that the program wouldn't check for cmds;
                data.envp = parsing(&data);
            if (reset_std_in_out_err(&data)) // remember to close fd{0,1,2} 
                return (free_all(data.envp), 1);
            /*
            int fd_tty;
            errno = 0;
            fd_tty = open("/dev/tty", O_RDWR);
            if (fd_tty == -1)
                perror("open error ");
            ft_putstr("something to do\n", fd_tty);
            printf("ttyslot ret: %d\n", ttyslot());
            printf("ttyname: %s\n", ttyname(fd_tty));
            (void)fd_tty;*/
        }
        free(data.p_rdl);
    }
    return(rl_clear_history(), free_all(data.envp), free_heredoc(&data, 0), data.status);
}

static int     exit_minishell(char **envp, char *p, int status, char *msg)
{
     free_all(envp);
     free(p);
     if (msg)
        printf("%s",msg);
     exit(status);
}

// static void    signal_handler(int signum)
// {
// 	(void)signum;
//     rl_replace_line("", 0);
//     write(1, "\n", 1);
//     rl_on_new_line();
//     rl_redisplay();
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