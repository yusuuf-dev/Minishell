#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void	execve_funct(char *s, char **arg)
{

	if (execve(s, arg, NULL) == -1)
	{
		printf("Error execve num : %d\n", errno);
		perror("");
	}
	exit(0);

}

int ft_pipe(void)
{
    int	    child_info = 0;
    int     first = 0;
    int     pipefd[2];
    pid_t   cpid;

    if (pipe(pipefd) == -1)
        return (perror(""), errno);
    cpid = fork();
    if (cpid == -1)
        return (perror(""), errno);
    
    if (cpid == 0)
    {
//	 char *s = "testing something\n";
        if (!first)
        {
        //    if (close(pipefd[0]) == -1)
          //   return (perror(""), errno);
            if (dup2(pipefd[1], 1) == -1)
             return (perror(""), errno);
        }
        else
        {
            if (dup2(1, pipefd[1]) == -1)
                return (perror(""), errno);
            if (dup2(0, pipefd[0]) == -1)
                return (perror(""), errno);
        }
//	write (1, s, strlen(s));
  //      exit(0);
  	return (0);
    }
    else
    {
        wait(&child_info);
    }
    if (WIFEXITED(child_info) && (WEXITSTATUS(child_info)))
        return (WEXITSTATUS(child_info));

    	first = 1;
/*            char test_pipe[1024];
        if (read(pipefd[0], test_pipe, 20) == -1)
        {
            perror("pipe read");
            exit (-1);
        }
        test_pipe[20] = 0;
        printf("stored in the pipe: %s\n", test_pipe);*/
	return (1);
}

int main(void)
{

	char *p[3] = {"/usr/bin/ls", "-la", NULL};
	if (!ft_pipe())
	{
		execve_funct("/usr/bin/ls", p);
	
	}
	char *p2[3] = {"/usr/bin/grep", "yes", NULL};
	execve_funct("/usr/bin/grep", p2);
	//	return (printf("error while piping\n"), 1);

	return (0);
}
