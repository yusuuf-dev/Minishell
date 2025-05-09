#include "minishell.h"

void    signal_handler(int signum)
{
	(void)signum;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}
static int assign_std_in_out_err(int *fd0, int *fd1, int *fd2)
{
    *fd0 = dup(0);
    if (*fd0 == -1)
        return (perror(""), 1);
    *fd1 = dup(1);
    if (*fd1 == -1)
        return (perror(""), 1);
    *fd2 = dup(2);
    if (*fd2 == -1)
        return (perror(""), 1);
    return (0);
}
static int reset_std_in_out_err(int fd0, int fd1, int fd2)
{
    if (dup2(fd0, 0) == -1)
        return (perror(""), 1);
    if (dup2(fd1, 1) == -1)
        return (perror(""), 1);
    if (dup2(fd2, 2) == -1)
        return (perror(""), 1);       
    return (0);
}
int main(int ac, char **av, char **envp)
{
	char *p = NULL;
    char **segments = NULL;
	struct sigaction C_slash;
    struct sigaction C_c;
	int	s_exit = 0;
    int status = 0;
    int fd0, fd1, fd2;

	(void)av;
	(void)ac;
	sigemptyset(&(C_slash.sa_mask));
    sigemptyset(&(C_c.sa_mask));
    C_slash.sa_flags = 0;
    C_c.sa_flags = 0;
    C_slash.sa_handler = SIG_IGN;
    C_c.sa_handler = signal_handler;
	envp = ft_duplicate(envp, 0);
    if (assign_std_in_out_err(&fd0, &fd1, &fd2))
        {return (free_all(envp), 1);}
	while (1 && !s_exit)
    {
		sigaction(SIGQUIT, &C_slash, NULL);
        sigaction(SIGINT, &C_c, NULL);
        if (reset_std_in_out_err(fd0, fd1, fd2))
            return (free_all(envp), 1);
		p = readline("minishell : ");
		if (!p)
		{
			printf("exit\n");
			free_all(envp);
			free(p);
			return (0);
		}
        p = ft_isspace_to_space(p);
        if (p[0])
        {
            i = found_pipe(p,envp);
            if (i == 1)
            {
                i = 0;
                segments = c_split(p, '|',envp);
                if (!segments)
                    return(exit_minishell(envp,p,1,"failed malloc\n"));//protect malloc            
                while(segments[i])
                {
                    envp = parsing(&segments[i], envp, &s_exit);
                    i++;    
                }
                free_all(segments);
                add_history(p);   
            }
            else if (i == 0)
            {
                    add_history(p);
                    envp = parsing(&p, envp, &s_exit, &status);
            }
            else
                return(exit_minishell(envp,p,1,"failed malloc\n"));//protect malloc            
            add_history(p);
            envp = parsing(&p, envp, &s_exit, &status);
        }
        free(p);
    }
    free_all(envp);
   	exit(status);
}

// static int     exit_minishell(char **envp, char *p, int status, char *msg)
// {
//     free_all(envp);
//     free(p);
//     if (msg)
//         printf("%s",msg);
//     exit(status);
// }

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