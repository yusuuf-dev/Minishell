/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:11:47 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/18 18:04:12 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*check for errno in case the wait did fail for another reason other than that the process doesn't have anymore children to wait for*/
/* wait for children and get the exit code of the last child*/


static int  wait_on_other_children(int rec_sig_quit, int rec_sig_int)
{
    int child_info;

    child_info = 0;
    while (wait(&child_info) != -1)
    {
       if (WIFSIGNALED(child_info) && ((WTERMSIG(child_info) + 128) == 130))
        {
            rec_sig_int = 1;
        }
        child_info = 0;
    }
    if (rec_sig_int)
    {
        write(1, "\n", 1);
    }
    if (rec_sig_quit)
    {
        ft_putstr("Quit (core dumped)\n", 1);
    }
    return (0);
}

static void  wait_children(pipes_t *pipe_data, t_data *data)
{
    int     child_info;
    int     rec_sig_int;
    int     rec_sig_quit;

    child_info = 0;
    rec_sig_int = 0;
    rec_sig_quit = 0;
    close(pipe_data->old_pipe);
    waitpid(pipe_data->cpid, &child_info, 0);// the end of pipeline, we don't need the old_pipe anymore;
    if (WIFEXITED(child_info))
        data->status = (WEXITSTATUS(child_info));
    else if (WIFSIGNALED(child_info))
    {
        data->status = WTERMSIG(child_info) + 128;
        if (data->status == 130)
            rec_sig_int = 1;
        else if (data->status == 131)
            rec_sig_quit = 1;
    }
    if (wait_on_other_children(rec_sig_quit, rec_sig_int)) // modify me
        return ; // in case wait fails ? probably will never fail check the man
    sigaction(SIGINT, &(data->SIG_INT), NULL);
    return ;
}

static void  close_save_old_pipe(pipes_t *pipe_data)
{
    if (pipe_data->i != 0)
        close(pipe_data->old_pipe);
    pipe_data->old_pipe = dup(pipe_data->pipefd[0]);
    if (pipe_data->old_pipe == -1)
        print_free_exit(DUP_FAILED, errno);
    close(pipe_data->pipefd[1]);
    close(pipe_data->pipefd[0]);
    return ;
}
/* this functions redirects stdin, stdout or both of them
    (depends on the position of the cmd in the pipeline)*/
/* It also flags the process as a child so that It won't give
    another prompt */
/* It resets old signals too*/
static void  redirecting_child_std(t_data *data, pipes_t *pipe_data)
{
    data->is_a_child = 1; // this to indicate later in the program that this process is a cmd from the pipeline
    /* reseting old signal handler*/
    sigaction(SIGINT, &(data->OLD_SIG_INT), NULL);
    sigaction(SIGQUIT, &(data->OLD_SIG_QUIT), NULL);
    data->p_rdl = ft_strdup(pipe_data->piped_cmds[pipe_data->i]);
    if (pipe_data->i == 0)
    {
        if (close(pipe_data->pipefd[0]))
            ;
        if (dup2(pipe_data->pipefd[1], STDOUT_FILENO) == -1)
            print_free_exit(DUP_FAILED, errno);
    }
    else if (pipe_data->piped_cmds[pipe_data->i + 1])
    {
        if (close(pipe_data->pipefd[0]))
            ;
        if (dup2(pipe_data->old_pipe, STDIN_FILENO) == -1 || dup2(pipe_data->pipefd[1], STDOUT_FILENO) == -1)
            print_free_exit(DUP_FAILED, errno);
    }
    else
    {
        if (dup2(pipe_data->old_pipe, STDIN_FILENO) == -1)
            print_free_exit(DUP_FAILED, errno);
    }
    return ;
}

void    ft_pipes(t_data *data)
{
    pipes_t pipe_data; // = ft_calloc(sizeof(pipes_t));

    ft_memset(&pipe_data, 0, sizeof(pipes_t));
    pipe_data.piped_cmds = data->segments;
    sigaction(SIGINT, &(data->S_SIG_IGN), NULL);
    while (pipe_data.piped_cmds[pipe_data.i])
    {
        if (pipe(pipe_data.pipefd) == -1)
            print_free_exit(PIPE_FAILED, errno);
        pipe_data.cpid = fork();
        if (pipe_data.cpid == -1)
            print_free_exit(FORK_FAILED, errno);
        if (pipe_data.cpid == 0)
            return (redirecting_child_std(data, &pipe_data)); // return (free_all(data->segments), 0);
        else
        {
            update_used_heredoc_list(pipe_data.piped_cmds[pipe_data.i], data, 0, 0);
            close_save_old_pipe(&pipe_data);
        }
        pipe_data.i += 1;
    }
    wait_children(&pipe_data, data);
    data->p_rdl = NULL;
    return ; //return (free_all(data->segments), free(data->p_rdl), *&(data->p_rdl) = NULL, 0);
}
