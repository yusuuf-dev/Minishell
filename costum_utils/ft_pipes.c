#include "../minishell.h"

int ft_pipes(char **piped_cmds, char **p, int *status, int *is_a_pipe)
{
    int	    child_info = 0;
    int     pos = 0;
    int     i = 0;
    int     pipefd_0[2];
    int     pipefd_1[2];
    pid_t   cpid;

    (void)*status;

   // if (pipe(pipefd_0) == -1)
    //    return (perror(""), errno);
    *is_a_pipe = 1;

    while (piped_cmds[i])
    {
        if (i % 2 == 0)
        {
            if (pipe(pipefd_0) == -1)
                return (perror(""), errno);
            if (pipe(pipefd_1) == -1)
                return (perror(""), errno);
        }
        cpid = fork();
        if (cpid == -1)
            return (perror(""), errno);
        *p = piped_cmds[i];
        if (cpid == 0)
        { // child
            if (!pos)
            {// I probably need to redirect the std in,out before I fork so 
                if (close(pipefd_0[0]) == -1) // closing the reading end of the pipe
                    return (perror(""), errno);
                if (dup2(pipefd_0[1], 1) == -1) // redirecting std out to the writing end of the pipe
                    return (perror(""), errno);
            }
            else if (pos == 1)
            {
                if (i % 2)
                {
                    if (close((pipefd_0[1]) == -1) == -1)
                        return (perror(""), errno);
                    if (dup2(pipefd_0[0], 0) == -1)
                        return (perror(""), errno);

                    if (close((pipefd_1[0]) == -1) == -1)
                        return (perror(""), errno);
                    if (dup2(pipefd_1[1], 1) == -1)
                        return (perror(""), errno);
                }
                else
                {
                    if (close((pipefd_1[1]) == -1) == -1)
                        return (perror(""), errno);
                    if (dup2(pipefd_1[0], 0) == -1)
                        return (perror(""), errno);

                    if (close((pipefd_0[0]) == -1) == -1)
                        return (perror(""), errno);
                    if (dup2(pipefd_0[1], 1) == -1)
                        return (perror(""), errno);
                }
            }
            else
            {
                if (i % 2)
                {
                    if (close(pipefd_0[1]) == -1)
                        return (perror(""), errno);
                    if (dup2(pipefd_0[0], 0) == -1)
                        return (perror(""), errno);
                }
                else
                {
                    if (close(pipefd_1[1]) == -1)
                        return (perror(""), errno);
                    if (dup2(pipefd_1[0], 0) == -1)
                        return (perror(""), errno);
                }
            }
            return (0);
        }
        else // parent
        {
            if (pos == 1)
            {
                if (i % 2 && close((pipefd_1[1]) == -1))
                    return (perror(""), errno);
                if (!(i % 2) && close((pipefd_0[1]) == -1))
                    return (perror(""), errno);
            }
            if (pos == 2) // meaning the last command
            {
                if (close(pipefd_0[1]) == -1 || close(pipefd_0[0]) == -1 || close(pipefd_1[1]) == -1 || close(pipefd_1[0]) == -1) // closing the std in, otherwise the running program on the other end of the pipe will keep waiting for input;
                    return (perror(""), errno);
            }
            waitpid(cpid, &child_info, 0);
           //wait(&child_info);
          // printf("child waiting status: %d\n", waitpid(cpid, &child_info, 0)); // check for error 
        }
        //printf("exited child num: %d\n", i);
        if (WIFEXITED(child_info) && WEXITSTATUS(child_info)) // in case there was an error in the execued command above meaning one of dmcs of pipe failed;
            return (WEXITSTATUS(child_info));
        if (piped_cmds[i + 1] && piped_cmds[i + 2]) // this updates the pos of the pipe, so we can know wether to redirect the output and input of the command;
            pos = 1;
        else
            pos = 2;
        i++;
    }
    *p = NULL;
    *is_a_pipe = 0;
    return (WEXITSTATUS(child_info)); // returns the exit code of the last child ??
}