#include "../minishell.h"

int ft_pipe(char **piped_cmds, char **p, int *status, int *is_a_pipe)
{
    int	    child_info = 0;
    int     pos = 0;
    int     i = 0;
    int     pipefd[2];
    pid_t   cpid;

    if (pipe(pipefd) == -1)
        return (perror(""), errno);
    *is_a_pipe = 1;

    while (piped_cmds[i])
    {
        cpid = fork();
        if (cpid == -1)
            return (perror(""), errno);
        
        if (cpid == 0)
        { // child
            if (!pos)
            {
                if (close(pipefd[0]) == -1)
                    return (perror(""), errno);
                if (dup2(1, pipefd[1]) == -1)
                    return (perror(""), errno);
            }
            else if (pos == 1)
            {
                if (dup2(1, pipefd[1]) == -1)
                    return (perror(""), errno);
                if (dup2(0, pipefd[0]) == -1)
                    return (perror(""), errno);
            }
            else
            {
                if (dup2(0, pipefd[0]) == -1)
                    return (perror(""), errno);
            }
            return (0);  
        }
        else // parent
        {
            wait(&child_info);
        }
        if (WIFEXITED(child_info) && WEXITSTATUS(child_info)) // in case there was an error in the execued command above meaning one of dmcs of pipe failed;
            return (WEXITSTATUS(child_info));
        if (piped_cmds[i + 1] && piped_cmds[i + 2]) // this updates the pos of the pipe, so we can know wether to redirect the output and input of the command;
            pos = 1;
        else
            pos = 2;
        i++;
    }
    *is_a_pipe = 0;
    return (WEXITSTATUS(child_info)); // returns the exit code of the last child ??
}