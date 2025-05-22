/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:11:47 by asoufian          #+#    #+#             */
/*   Updated: 2025/05/21 11:11:50 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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
static int  wait_children(pipes_t *pipe_data, unsigned char *status);
static int  fork_and_create_pipe(pipes_t *pipe_data);

int ft_pipes(char **piped_cmds, char **p, unsigned char *status, int *is_a_pipe)
{
    pipes_t *pipe_data = ft_calloc(sizeof(pipes_t));
  //  __sighandler_t old_handler;

    pipe_data->is_a_pipe = is_a_pipe;
    pipe_data->piped_cmds = piped_cmds;
    while (piped_cmds[pipe_data->i])
    {
        if (fork_and_create_pipe(pipe_data))
            return (perror(""), errno);
        if (pipe_data->cpid == 0)
        {
            if (redirecting_child_std(pipe_data, p))
                return (errno);
            return (0);
        }
        else
        {
         //   old_handler = signal(SIGINT, SIG_IGN);
            if (redirecting_pipes(pipe_data))
                return (errno);
        }
    }
    if (wait_children(pipe_data, status))
        return (errno);
  //  signal(SIGINT, old_handler);
    return (free_all(piped_cmds), *p = NULL, *is_a_pipe = 0, free(pipe_data), 0);
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
extern volatile sig_atomic_t f_sig;

static void    count_sigs(int signum)
{
    (void)signum;
    f_sig = 2;
}

static int  wait_children(pipes_t *pipe_data, unsigned char *status)
{
    int     child_info;
    struct sigaction C_c_alt;
	struct sigaction old_C_c;
	sigemptyset(&(C_c_alt.sa_mask));
	C_c_alt.sa_flags = SA_RESTART;
    C_c_alt.sa_handler = count_sigs;
    //__sighandler_t old_handler;

    if (sigaction(SIGINT, &C_c_alt, &old_C_c) == -1)
        return (perror(""), errno);
    child_info = 0;
    //old_handler = signal(SIGINT, SIG_IGN);
    if ((close(pipe_data->old_pipe) == -1) || (waitpid(pipe_data->cpid, &child_info, 0) == -1))// the end of pipeline, we don't need the old_pipe anymore;
        return (perror(""), errno);
    if (WIFEXITED(child_info))
        *status = (WEXITSTATUS(child_info));
    else if (WIFSIGNALED(child_info))
        *status = ((child_info & 127) + 128);
    while (wait(NULL) != -1)
        ;
    if (errno != ECHILD)
        return (perror(""), errno);
    if (sigaction(SIGINT, &old_C_c, NULL) == -1)
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
    *p = pipe_data->piped_cmds[pipe_data->i];
    *(pipe_data->is_a_pipe) = 1;
    if (pipe_data->i == 0)
    {
        if (dup2(pipe_data->pipefd[1], 1) == -1 || close(pipe_data->pipefd[0]) == -1)
            return (perror(""), errno);
    }
    else if (pipe_data->piped_cmds[pipe_data->i + 1])
    {
        if (dup2(pipe_data->old_pipe, 0) == -1 || dup2(pipe_data->pipefd[1], 1) == -1 || close(pipe_data->pipefd[0]) == -1)
            return (perror(""), errno);
    }
    else
    {
        if (dup2(pipe_data->old_pipe, 0))
            return (perror(""), errno);
    }
    return (0);
}
