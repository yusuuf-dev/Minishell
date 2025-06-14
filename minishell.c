#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
    int i;
    t_data data;

	(void)av; // maybe we can remove these two from the argument since we don't use them, the problem is wether the envp will work or not;
	(void)ac; //
    ft_setup(&data, envp);
    if (assign_std_in_out_err(&data))
        {return (free_all(envp), errno);}
	while (!(data.exit) && !(data.is_a_pipe))
    {
		sigaction(SIGQUIT, &(data.C_slash), NULL);
        sigaction(SIGINT, &(data.C_c), NULL);
		data.p_rdl = readline("minishell : ");
        if (f_sig)
        {
            data.status = 130;
            f_sig = 0;
        }
		if (!data.p_rdl) // C^d
			return (ft_putstr("exit\n", 1), free_all(data.envp), free(data.p_rdl), rl_clear_history(), free_heredoc(&data, 1), data.status);
        add_history(data.p_rdl);
        if (check_syntax(data.p_rdl))
            data.status = 2;
        else if (here_doc_fork(&(data.p_rdl), &(data.status), &data))
            return (errno);
        else if (data.p_rdl && data.p_rdl[0])
        {
       //     add_history(data.p_rdl);
            i = found_pipe(data.p_rdl);
            if (i == 1)
            {
                data.segments = c_split(data.p_rdl, '|', data.envp, &(data.status));
                if (!data.segments)
                    return(exit_minishell(data.envp, data.p_rdl, 1, "failed malloc\n"));//protect malloc
                if (ft_pipes(&data))
                    return (errno);
            }
            else if (i == -1)
            {
                data.status = 2;
                return(exit_minishell(data.envp, data.p_rdl, 1, "failed malloc\n"));//protect malloc
            }
            if (data.p_rdl)  // not great, this is done for when the piping is done so that the program wouldn't check for cmds;
                data.envp = parsing(&data);
            if (reset_std_in_out_err(&data))
                return (free_all(data.envp), 1);
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


// #include "minishell.h"

// static int exit_minishell(char **envp, char *p, int status, char *msg);

// // volatile sig_atomic_t child_exists = 0;
// volatile sig_atomic_t f_sig = 0;

// void signal_handler(int signum)
// {
//     (void)signum;
//     //  status = 130;
//     //  write(1, "here\n", 5);
//     if (f_sig != 2)
//     {
//         rl_replace_line("", 0);
//         write(1, "\n", 1);
//         rl_on_new_line();
//         rl_redisplay();
//     }
//     else
//         write(1, "\n", 1);
//     f_sig = 1;
// }
// /*void    ignoree(int signum)
// {
//     (void)signum;
//     return;
//     rl_replace_line("", 0);
//     //rl_on_new_line();
//     rl_redisplay();
// }*/
// static int assign_std_in_out_err(int *fd0, int *fd1, int *fd2)
// {
//     *fd0 = dup(0);
//     if (*fd0 == -1)
//         return (perror(""), 1);
//     *fd1 = dup(1);
//     if (*fd1 == -1)
//         return (perror(""), 1);
//     *fd2 = dup(2);
//     if (*fd2 == -1)
//         return (perror(""), 1);
//     return (0);
// }
// static int reset_std_in_out_err(int fd0, int fd1, int fd2)
// {
//     if (dup2(fd0, 0) == -1)
//         return (perror(""), 1);
//     if (dup2(fd1, 1) == -1)
//         return (perror(""), 1);
//     if (dup2(fd2, 2) == -1)
//         return (perror(""), 1);
//     return (0);
// }
// int main(int ac, char **av, char **envp)
// {
//     char *p = NULL;
//     char **segments = NULL;
//     struct sigaction C_slash;
//     struct sigaction C_c;

//     int s_exit = 0;
//     unsigned char status = 0;
//     int is_a_pipe = 0;
//     int fd0, fd1, fd2;
//     int i;
//     //    t_data *data;

//     if (ac != 1 || av[1])
//         return (ft_putstr("minishell doesn't require argements\n", 2), 1);

//     sigemptyset(&(C_slash.sa_mask));
//     sigemptyset(&(C_c.sa_mask));
//     C_slash.sa_flags = SA_RESTART;
//     C_c.sa_flags = 0;
//     C_slash.sa_handler = SIG_IGN;
//     // C_slash.sa_handler = ignoree;
//     C_c.sa_handler = signal_handler;
//     envp = ft_duplicate(envp, 0);
//     if (assign_std_in_out_err(&fd0, &fd1, &fd2))
//     {
//         return (free_all(envp), 1);
//     }
//     // data = ft_setup(envp);
//     while (1 && !s_exit && !is_a_pipe)
//     {
//         sigaction(SIGQUIT, &C_slash, NULL);
//         sigaction(SIGINT, &C_c, NULL);
//         if (f_sig)
//         {
//             status = 130;
//             f_sig = 0;
//         }
//         p = readline("minishell : ");
//         if (!p)
//         {
//             printf("exit\n");
//             free_all(envp);
//             free(p);
//             rl_clear_history();
//             return (status);
//         }
//         if (!ft_isspace_to_space(&p))
//         {
//             add_history(p);
//             i = found_pipe(p);
//             if (i == 1)
//             {
//                 segments = c_split(p, '|', envp, &status);
//                 if (!segments)
//                     return (exit_minishell(envp, p, 1, "failed malloc\n")); // protect malloc
//                 free(p);
//                 if (ft_pipes(segments, &p, &status, &is_a_pipe))
//                     return (errno);
//             }
//             else if (i == -1)
//             {
//                 ft_putstr("minishell: syntax error\n", 2);
//                 status = 2;
//             }
//             else
//                 envp = parsing(&p, envp, &s_exit, &status, is_a_pipe);
//             if (reset_std_in_out_err(fd0, fd1, fd2))
//                 return (free_all(envp), 1);
//         }
//         free(p);
//     }
//     rl_clear_history();
//     free_all(envp);
//     return (status);
// }

// static int exit_minishell(char **envp, char *p, int status, char *msg)
// {
//     free_all(envp);
//     free(p);
//     if (msg)
//         printf("%s", msg);
//     exit(status);
// }

