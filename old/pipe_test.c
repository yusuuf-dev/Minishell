#include <unistd.h>
#include <stdio.h>

int ft_pipe(char **piped_cmds, int *status, int *is_a_pipe)
{
    int	    child_info = 0;
    int     first = 0;
    int     pipefd[2];
    pid_t   cpid;

    if (pipe(pipefd) == -1)
        return (perror(""), errno);
    *is_a_pipe = 1;
    cpid = fork();
    if (cpid == -1)
        return (perror(""), errno);
    
    if (cpid == 0)
    {
        if (!first)
        {
            if (close(pipefd[0]) == -1)
             return (perror(""), errno);
            if (dup2(1, pipefd[1]) == -1)
             return (perror(""), errno);
        }
        else
        {
            if (dup2(1, pipefd[1]) == -1)
                return (perror(""), errno);
            if (dup2(0, pipefd[0]) == -1)
                return (perror(""), errno);
        }
        return (0);
        // child
    }
    else
    {
        wait(&child_info);
    }
    if (WIFEXITED(child_info))
        return (WEXITSTATUS(child_info));
    first = 1;
}


