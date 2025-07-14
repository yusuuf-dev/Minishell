#include "../minishell.h"

extern volatile sig_atomic_t f_sig;

typedef struct pipes
{
    int     i;
    pid_t   cpid;
    int     pipefd[2];
    int     old_pipe;
    char    **piped_cmds;
    int     *is_a_pipe;
} pipes_t;

static int  redirecting_child_std(pipes_t *pipe_data, char **p);
static int  redirecting_pipes(pipes_t *pipe_data);
static int  wait_children(pipes_t *pipe_data, unsigned char *status, t_data *data);
static int  fork_and_create_pipe(pipes_t *pipe_data);

int ft_pipes(t_data *data)
{
    pipes_t pipe_data; // = ft_calloc(sizeof(pipes_t));

    ft_memset(&pipe_data, 0, sizeof(pipes_t));
    pipe_data.is_a_pipe = &(data->is_a_pipe);
    pipe_data.piped_cmds = data->segments;
    while (pipe_data.piped_cmds[pipe_data.i])
    {
        if (fork_and_create_pipe(&pipe_data))
            return (perror(""), errno);
        if (pipe_data.cpid == 0)
        {
            data->is_a_pipe = 1;
            if (redirecting_child_std(&pipe_data, &(data->p_rdl)))
                return (errno);
            //return (free_all(data->segments), 0);
            return (0);
        }
        else
        {
            if (redirecting_pipes(&pipe_data))
                return (errno);
        }
    }
    if (wait_children(&pipe_data, &(data->status), data))
        return (errno);
    //return (free_all(data->segments), free(data->p_rdl), *&(data->p_rdl) = NULL, 0);
    return (*&(data->p_rdl) = NULL, 0);
}

/*check for errno in case the wait did fail for another reason other than that the process doesn't have anymore children to wait for*/
/* wait for children and get the exit code of the last child*/

static int  fork_and_create_pipe(pipes_t *pipe_data)
{
    if (pipe(pipe_data->pipefd) == -1)
        return (perror(""), errno);
    pipe_data->cpid = fork();
    if (pipe_data->cpid == -1)
        return (perror(""), errno);
    return (0);
}

static int  wait_children(pipes_t *pipe_data, unsigned char *status, t_data *data)
{
    int     child_info;
    //__sighandler_t old_handler;

    if (sigaction(SIGINT, &(data->C_c_alt), NULL) == -1)
        return (perror(""), errno);
    child_info = 0;
    //old_handler = signal(SIGINT, SIG_IGN);
    int i = 0;
    if ((close(pipe_data->old_pipe) == -1) || ((i = waitpid(pipe_data->cpid, &child_info, 0)) == -1))// the end of pipeline, we don't need the old_pipe anymore;
        return (perror(""), errno);
    if (WIFEXITED(child_info))
        *status = (WEXITSTATUS(child_info));
    else if (WIFSIGNALED(child_info))
        *status = ((child_info & 127) + 128);
    while (wait(NULL) != -1)
        ;
    if (errno != ECHILD)
        return (perror(""), errno);
    if (sigaction(SIGINT, &(data->C_c), NULL) == -1)
        return (perror(""), errno);
    if (f_sig == 2 && kill(0, SIGINT))
        return (perror(""), errno);
   // signal(SIGINT, old_handler);
    return (0);
}
static int  redirecting_pipes(pipes_t *pipe_data)
{
    if (pipe_data->i != 0 && close(pipe_data->old_pipe) == -1)
        return (perror(""), errno);
    pipe_data->old_pipe = dup(pipe_data->pipefd[0]);
    if (close(pipe_data->pipefd[1]) == -1 || pipe_data->old_pipe == -1 || close(pipe_data->pipefd[0]) == -1)
        return (perror(""), errno);
    pipe_data->i += 1;
    return (0);
}
static int  redirecting_child_std(pipes_t *pipe_data, char **p)
{
    signal(SIGQUIT, SIG_DFL);
    // free(*p);
    *p = ft_strdup(pipe_data->piped_cmds[pipe_data->i]);
    *(pipe_data->is_a_pipe) = 1;
    if (pipe_data->i == 0)
    {
        if (dup2(pipe_data->pipefd[1], 1) == -1 || close(pipe_data->pipefd[0]) == -1 || close(pipe_data->pipefd[1]) == -1)
            return (perror(""), errno);
    }
    else if (pipe_data->piped_cmds[pipe_data->i + 1])
    {
        if (dup2(pipe_data->old_pipe, 0) == -1 || dup2(pipe_data->pipefd[1], 1) == -1 || close(pipe_data->pipefd[0]) == -1 || close(pipe_data->pipefd[1]) == -1 || close(pipe_data->old_pipe) == -1)
            return (perror(""), errno);
    }
    else
    {
        if (dup2(pipe_data->old_pipe, 0) || close(pipe_data->old_pipe) == -1)
            return (perror(""), errno);
    }
    return (0);
}