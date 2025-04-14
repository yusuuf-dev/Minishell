#include "minishell.h"

void    signal_handler(int signum)
{
	(void)signum;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

int main(int ac, char **av, char **envp)
{
	char *p = NULL;
	struct sigaction C_slash;
    struct sigaction C_c;
	int	s_exit = 0;

	(void)av;
	(void)ac;
	sigemptyset(&(C_slash.sa_mask));
    sigemptyset(&(C_c.sa_mask));
    C_slash.sa_flags = 0;
    C_c.sa_flags = 0;
    C_slash.sa_handler = SIG_IGN;
    C_c.sa_handler = signal_handler;
	envp = ft_duplicate(envp);
	while (1 && !s_exit)
    {
		sigaction(SIGQUIT, &C_slash, NULL);
        sigaction(SIGINT, &C_c, NULL);
		p = readline("minishell : ");
		if (!p)
		{
			printf("exit\n");
			free_all(envp);
			free(p);
			exit(0);
		}
    if (p[0])
    {
        envp = parsing(p, envp, &s_exit);
        add_history(p);
    }
    free(p);
    }
   	exit(s_exit); 
}
