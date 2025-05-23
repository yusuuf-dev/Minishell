#include "../minishell.h"

int ft_pipes(char **piped_cmds, char **p, unsigned char *status, int *is_a_pipe)
{
    int	    child_info = 0;
    int     pos = 0;
    int     i = 0;
    int     pipefd_0[2];
    int     pipefd_1[2];
    pid_t   cpid;

    (void)*status;
    *is_a_pipe = 1;
    while (piped_cmds[i])
    {
        *p = piped_cmds[i];
        if ((!i || ((i % 2) && i > 1)) && pipe(pipefd_1) == -1)
            return (perror(""), errno);
        if ((!i || (!(i % 2) && i > 1)) && pipe(pipefd_0) == -1)
            return (perror(""), errno);
        cpid = fork();
        if (cpid == -1)
            return (perror(""), errno);
        if (cpid == 0)
        { // child   // maybe split every single pos possibelity into functs ??
            if (!pos)
            {// I probably need to redirect the std in,out before I fork so 
                if (close(pipefd_0[0]) == -1 || dup2(pipefd_0[1], 1) == -1) //closing the reading end of the pipe
                    return (perror(""), errno); //redirecting std out to the writing end of the pipe
            }
            else if (pos == 1)
            {
                if (i % 2 && (close(pipefd_0[1]) == -1 || dup2(pipefd_0[0], 0) == -1 || close(pipefd_1[0]) == -1 || dup2(pipefd_1[1], 1) == -1))
                        return (perror(""), errno);
                if (!(i % 2) && (close(pipefd_1[1]) == -1 || dup2(pipefd_1[0], 0) == -1 || close(pipefd_0[0]) == -1 || dup2(pipefd_0[1], 1) == -1))
                        return (perror(""), errno);
            }
            else
            {
                if (i % 2 && (close(pipefd_1[0]) == -1 || close(pipefd_1[1]) == -1 || close(pipefd_0[1]) == -1 || dup2(pipefd_0[0], 0) == -1))
                        return (perror(""), errno);
                if (!(i % 2) && (close(pipefd_0[0]) == -1 || close(pipefd_0[1]) == -1 || close(pipefd_1[1]) == -1 || dup2(pipefd_1[0], 0) == -1))
                        return (perror(""), errno);
            }
            return (0);
        }
        else // parent
        {
            if (pos == 1 )//|| !pos)
            {
                if (i % 2 && ((close(pipefd_0[0]) == -1) || (close(pipefd_0[1]) == -1))) //|| close((pipefd_1[1]) == -1)))
                    return (perror(""), errno);
                if (!(i % 2) && ((close(pipefd_1[0]) == -1) || (close(pipefd_1[1]) == -1))) //|| close((pipefd_0[1]) == -1)))
                    return (perror(""), errno);
            }
            if (pos == 2 && (close(pipefd_0[1]) == -1 || close(pipefd_0[0]) == -1 || close(pipefd_1[1]) == -1 || close(pipefd_1[0]) == -1)) // meaning the last command
                    return (perror(""), errno); // closing the std in, otherwise the running program on the other end of the pipe will keep waiting for input;
            waitpid(cpid, &child_info, 0);
        }
        if (WIFEXITED(child_info) && WEXITSTATUS(child_info)) // in case there was an error in the execued command above meaning one of dmcs of pipe failed;
            *status = (WEXITSTATUS(child_info));
            //return (WEXITSTATUS(child_info));
        pos = (piped_cmds[i + 1] && piped_cmds[i + 2]) ? 1 : 2; // this indicates wether the cmds is the last in the list by setting pos to 2.
        i++;
    }
    // free_all(piped_cmds);
    *p = NULL;
    *is_a_pipe = 0;
    //return (WEXITSTATUS(child_info)); // returns the exit code of the last child ??
    return (0);
}