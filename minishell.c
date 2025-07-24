#include "minishell.h"

extern volatile sig_atomic_t f_sig;
// static int     exit_minishell(char **envp, char *p, int status, char *msg);

static int reset_std_in_out_err(t_data *data)
{
    if (dup2(data->fd0, STDIN_FILENO) == -1)
        print_free_exit(DUP_FAILED, errno);
    if (dup2(data->fd1, STDOUT_FILENO) == -1)
        print_free_exit(DUP_FAILED, errno);
    if (dup2(data->fd2, STDERR_FILENO) == -1)
        print_free_exit(DUP_FAILED, errno);       
    return (0);
}
// static void reset_ptrs_2_null(t_data *data)
// {
//     void    *envp;
//     unsigned char status;

//     memset(data, 0, sizeof((void *) * 8));
//     /*status = data->status;
//     envp = data->envp;
    
//     data->envp = envp;
//     data->status = status;*/
// }
int main(int ac, char **av, char **envp)
{
    t_data data;

    ft_setup(&data, envp, ac, av);
	while (!(data.exit) && !(data.is_a_child))
    {
        sigaction(SIGINT, &(data.SIG_INT), NULL);
		sigaction(SIGQUIT, &(data.S_SIG_IGN), NULL);
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
			return (rl_clear_history(), config_malloc(NULL, 0, 2), data.status);
        }
        if (data.p_rdl[0] && !check_syntax(&data))
        {
            here_doc(&data);
            if (data.p_rdl && data.p_rdl[0])
            {
                if (found_pipe(data.p_rdl))
                {
                    data.segments = skip_quotes_split(data.p_rdl, '|');
                    ft_pipes(&data); // find a way to get the data into config_malloc maybe ? so that I won't have to check here for error
                }
                if (data.p_rdl)  // not great, this is done for when the piping is done so that the program wouldn't check for cmds;
                    parsing(&data);
                reset_std_in_out_err(&data); // remember to close fd{0,1,2}
            }
        }
       memset(&data, 0, (sizeof(void *) * PTR_TO_NULL));
       config_malloc(NULL, 0, 0);
    }
    return(rl_clear_history(), config_malloc(NULL, 0, 2), data.status);
}

