#include "minishell.h"

extern volatile sig_atomic_t f_sig;
// static int     exit_minishell(char **envp, char *p, int status, char *msg);

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
    if (assign_std_in_out_err(&data))
        {return (config_malloc(NULL,0), errno);}
	while (!(data.exit) && !(data.is_a_pipe))
    {
        if (sigaction(SIGINT, &(data.SIG_INT), NULL) == -1) // remember to remove all the if condition on sigaction
            return (perror (""), errno);                    // check the man for possible errors
		if (sigaction(SIGQUIT, &(data.S_SIG_IGN), NULL) == -1)
            return (perror (""), errno);
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
        if (!data.is_a_pipe)
            free(data.p_rdl);
       // config_malloc(NULL,0);
    }
    return(close_dup_fds(&data), rl_clear_history(), config_malloc(NULL,0), data.status);
}