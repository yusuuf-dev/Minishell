/*int ft_pipes(char **piped_cmds, char **p, unsigned char *status, int *is_a_pipe)
{
    int	    child_info = 0;
    int     pos = 2;
    int     i = 0;
    int     pipefd_0[2];
    int     pipefd_1[2];
    pid_t   cpid;
    pid_t   cpid_2;

    *is_a_pipe = 1;
    if (pipe(pipefd_1) == -1 || pipe(pipefd_0) == -1)
        return (perror(""), errno);
    while (piped_cmds[i])
    {
        child_info = 0;
        *p = piped_cmds[i];
        if (!(piped_cmds[i + 1]))
            pos = 0;
        cpid = fork();
        if (cpid == -1)
            return (perror(""), errno);
        if (cpid == 0)
        { // child   // maybe split every single pos possibelity into functs ??
            if (!i)
            {// I probably need to redirect the std in,out before I fork so 
                if (close(pipefd_0[0]) == -1 || dup2(pipefd_0[1], STDOUT_FILENO) == -1 || close(pipefd_0[1]) == -1 || close(pipefd_1[0]) == -1 || close(pipefd_1[1])) //closing the reading end of the pipe
                    return (perror(""), errno); //redirecting std out to the writing end of the pipe
            }
            else if (piped_cmds[i + 1])
            {
                if ((close(pipefd_0[0]) == -1 || dup2(pipefd_1[0], STDIN_FILENO) == -1 || dup2(pipefd_0[1], STDOUT_FILENO) == -1) || close(pipefd_0[1]) == -1 || close(pipefd_1[0]) == -1)
                    return (perror(""), errno);
            }
            else
            {
                if (close(pipefd_0[0]) == -1 || close(pipefd_0[1]) == -1 || (dup2(pipefd_1[0], STDIN_FILENO) == -1) || close(pipefd_1[0]) == -1)
                    return (perror(""), errno);
            }
            return (0);
        }
        else // parent
        {
            if (!i && close(pipefd_1[1]) == -1)
                return (perror(""), errno);
            if (piped_cmds[i + 1] == NULL && (close(pipefd_0[0]) == -1) && (close(pipefd_1[1]) == -1))
                return (perror(""), errno);
            if ((close(pipefd_0[1]) == -1) || (close(pipefd_1[0]) == -1) || (pipe(pipefd_1) == -1))
                return (perror(""), errno);
            if (piped_cmds[i + 1]) // there's another part of the pipe
            {
                if (!(piped_cmds[i + 2]))
                    pos = 1;
                cpid_2 = fork();
                *p = piped_cmds[i + 1];
                if (cpid_2 == -1)
                    return (perror(""), errno);
                if (cpid_2 == 0)
                {
                    if (piped_cmds[i + 2]) // there's another command needs to be executed, that means this is not the last one, redirect stdout to pipe;
                    {
                        if (close(pipefd_1[0]) == -1 || (dup2(pipefd_0[0], STDIN_FILENO) == -1 ||  dup2(pipefd_1[1], STDOUT_FILENO) == -1) || close(pipefd_0[0]) == -1 || close(pipefd_1[1]) == -1)
                            return (perror(""), errno);
                    }
                    else // this is the last command in list of piped commands, no need to redirect stdout
                    {
                        if ((close(pipefd_1[0]) == -1 || close(pipefd_1[1]) == -1 || dup2(pipefd_0[0], STDIN_FILENO) == -1) || close(pipefd_0[0]) == -1) // close(pipefd_0[1]) == -1 ||
                            return (perror(""), errno);
                    }
                    return (0);
                }
                else
                {
                    if (pos == 1 && ((close(pipefd_1[1]) == -1) || (close(pipefd_1[0]) == -1) || (close(pipefd_0[0]) == -1))) // end of the pipe; close all
                        return (perror(""), errno);
                    if (pos != 1)
                    {
                        if ((close(pipefd_0[0]) == -1) || (close(pipefd_1[1]) == -1) || (pipe(pipefd_0) == -1)) // there are still more commands in the pipe
                            return (perror(""), errno);
                    }
                    waitpid(cpid, &child_info, 0);
                    waitpid(cpid_2, &child_info, 0); // change child_info
                    if (WIFEXITED(child_info)) // in case there was an error in the execued command above meaning one of dmcs of pipe failed;
                        *status = (WEXITSTATUS(child_info));
                    child_info = 0;
                }
            }
            if (!pos)
            {
                if (!pos && ((close(pipefd_1[0]) == -1) || (close(pipefd_1[1]) == -1))) //|| ))// end of commands 
                    return (perror(""), errno);
                waitpid(cpid, &child_info, 0);
            }
        }
        if (!pos && WIFEXITED(child_info)) // in case there was an error in the execued command above meaning one of dmcs of pipe failed;
            *status = (WEXITSTATUS(child_info));
        if((!piped_cmds[i + 1]) || (!(piped_cmds[i + 2])))
        {
            break;
        }
        i += 2;
    }
    /*if (pos && ((close(pipefd_0[0]) == -1) || (close(pipefd_0[1]) == -1) || (close(pipefd_1[0]) == -1)))
        return (perror(""), errno);
    if (!pos && ((close(pipefd_1[0]) == -1) || (close(pipefd_1[1]) == -1)))// || (close(pipefd_0[0]) == -1))
        return (perror(""), errno);//
    // close all pipes;
    free_all(piped_cmds);
    *p = NULL;
    *is_a_pipe = 0;
    //return (WEXITSTATUS(child_info)); // returns the exit code of the last child ??
    return (0);
}*/
