/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:11:47 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/16 10:50:55 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  redirecting_child_std(t_data *data, pipes_t *pipe_data, char **p);
static int  redirecting_pipes(pipes_t *pipe_data);
static int  wait_children(pipes_t *pipe_data, unsigned char *status, t_data *data);
static int  fork_and_create_pipe(pipes_t *pipe_data, t_data *data);

int update_used_heredoc_list(char *s, t_data *data)
{
    t_heredoc *temp = data->heredooc;
    int     f_d = 0;
    int     f_s = 0;
    int     found = 0;
    int     i = 0;

	while ((s)[i] && !found)
	{
		if ((s)[i] == '\'' && !f_d)
			f_s = !f_s;
        if ((s)[i] == '\"' && !f_s)
            f_d = !f_d;
		if (!f_d && !f_s && (s)[i] == '<' && (s)[i + 1] == '<') // I don't have to check wether the heredoc is valid cuz we have check_syntax for that;
            found = 1;
		i++;
	}
    if (!temp || !found)
        return (1);
    while(temp->next && temp->arg_num)
	{
		temp = temp->next;
	}
    temp->arg_num = 1;
    return (1); // just so I can bypass norminette
}
int ft_pipes(t_data *data)
{
    pipes_t pipe_data; // = ft_calloc(sizeof(pipes_t));

    ft_memset(&pipe_data, 0, sizeof(pipes_t));
    pipe_data.piped_cmds = data->segments;
    sigaction(SIGINT, &(data->S_SIG_IGN), NULL);
    while (pipe_data.piped_cmds[pipe_data.i])
    {
        if (fork_and_create_pipe(&pipe_data, data))
            return (perror(""), errno);
        if (pipe_data.cpid == 0)
        {
            if (redirecting_child_std(data, &pipe_data, &(data->p_rdl)))
                return (errno);
           return (0); // return (free_all(data->segments), 0);
        }
        else
        {
            if (update_used_heredoc_list(pipe_data.piped_cmds[pipe_data.i], data) && redirecting_pipes(&pipe_data))
                return (errno);
        }
    }
    if (wait_children(&pipe_data, &(data->status), data))
        return (errno);
    return (*&(data->p_rdl) = NULL, 0); //return (free_all(data->segments), free(data->p_rdl), *&(data->p_rdl) = NULL, 0);
}

/*check for errno in case the wait did fail for another reason other than that the process doesn't have anymore children to wait for*/
/* wait for children and get the exit code of the last child*/

static int  fork_and_create_pipe(pipes_t *pipe_data, t_data *data)
{
    (void)data;
    if (pipe(pipe_data->pipefd) == -1)
        return (perror(""), errno);
    pipe_data->cpid = fork();
    if (pipe_data->cpid == -1)
        return (perror(""), errno);
    return (0);
}

static int  wait_on_other_children(int rec_sig_quit, int rec_sig_int)
{
    int child_info;

    child_info = 0;
    while (wait(&child_info) != -1)
    {
       // if (WIFSIGNALED(child_info) && ((child_info & 127) + 128) == 130)
       if (WIFSIGNALED(child_info) && ((WTERMSIG(child_info) + 128) == 130))
        {
            rec_sig_int = 1;
        }
        child_info = 0;
    }
  /*  if (errno != ECHILD)
        return (perror(""), errno);*/
    if (rec_sig_quit)
    {
        ft_putstr("Quit (core dumped)\n", 1);
    }
    else if (rec_sig_int)
    {
        write(1, "\n", 1);
    }
    return (0);
}

static int  wait_children(pipes_t *pipe_data, unsigned char *status, t_data *data)
{
    int     child_info;
    int     rec_sig_int;
    int     rec_sig_quit;

    child_info = 0;
    rec_sig_int = 0;
    rec_sig_quit = 0;
    if ((close(pipe_data->old_pipe) == -1) || (waitpid(pipe_data->cpid, &child_info, 0) == -1))// the end of pipeline, we don't need the old_pipe anymore;
        return (perror(""), errno);
    if (WIFEXITED(child_info))
        *status = (WEXITSTATUS(child_info));
    else if (WIFSIGNALED(child_info))
    {
        //*status = ((child_info & 127) + 128);
        *status = WTERMSIG(child_info) + 128;
        if (*status == 130)
            rec_sig_int = 1;
        else if (*status == 131)
            rec_sig_quit = 1;
    }
    if (wait_on_other_children(rec_sig_quit, rec_sig_int))
        return (errno); // in case wait fails ? probably will never fail check the man
    if (sigaction(SIGINT, &(data->SIG_INT), NULL) == -1)
        return (perror(""), errno);
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

static int  redirecting_child_std(t_data *data, pipes_t *pipe_data, char **p)
{
    data->is_a_pipe = 1; // this to indicate later in the program that this process is a cmd from the pipeline
    /* reseting old signal handler*/
    sigaction(SIGINT, &(data->OLD_SIG_INT), NULL);
    sigaction(SIGQUIT, &(data->OLD_SIG_QUIT), NULL);
  ///  free(*p);
    *p = ft_strdup(pipe_data->piped_cmds[pipe_data->i]);
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