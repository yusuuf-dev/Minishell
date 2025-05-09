#include "minishell.h"

void    signal_handler(int signum)
{
	(void)signum;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}
static int assign_std_in_out_err(int *fd0, int *fd1, int *fd2)
{
    *fd0 = dup(0);
    if (*fd0 == -1)
        return (perror(""), 1);
    *fd1 = dup(1);
    if (*fd1 == -1)
        return (perror(""), 1);
    *fd2 = dup(2);
    if (*fd2 == -1)
        return (perror(""), 1);
    return (0);
}
static int reset_std_in_out_err(int fd0, int fd1, int fd2)
{
    if (dup2(fd0, 0) == -1)
        return (perror(""), 1);
    if (dup2(fd1, 1) == -1)
        return (perror(""), 1);
    if (dup2(fd2, 2) == -1)
        return (perror(""), 1);       
    return (0);
}
int main(int ac, char **av, char **envp)
{
	char *p = NULL;
	struct sigaction C_slash;
    struct sigaction C_c;
	int	s_exit = 0;
    int status = 0;
    int is_a_pipe = 0;
    int fd0, fd1, fd2;

	(void)av; // maybe we can remove these two from the argument since we don't use them, the problem is wether the envp will work or not;
	(void)ac; //
	sigemptyset(&(C_slash.sa_mask));
    sigemptyset(&(C_c.sa_mask));
    C_slash.sa_flags = 0;
    C_c.sa_flags = 0;
    C_slash.sa_handler = SIG_IGN;
    C_c.sa_handler = signal_handler;
	envp = ft_duplicate(envp, 0);
    if (assign_std_in_out_err(&fd0, &fd1, &fd2))
        {return (free_all(envp), 1);}
	while (1 && !s_exit && !is_a_pipe)
    {
		sigaction(SIGQUIT, &C_slash, NULL);
        sigaction(SIGINT, &C_c, NULL);
        if (reset_std_in_out_err(fd0, fd1, fd2))
            return (free_all(envp), 1);
		p = readline("minishell : ");
		if (!p)
		{
			printf("exit\n");
			free_all(envp);
			free(p);
			return (0);
		}
        if (p[0])
        {
            add_history(p);
            envp = parsing(&p, envp, &s_exit, &status);
        }
        free(p);
    }
    free_all(envp);
    return (status);
   	//exit(status);
}
