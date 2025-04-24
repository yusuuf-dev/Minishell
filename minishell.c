#include "minishell.h"

void    signal_handler(int signum)
{
	(void)signum;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}
static int    set_default_fd(char *term_path)
{
    size_t  i = 0;
    int     temp_fd = 0;

    while (i < 3)
    {
        if (!isatty(i))
        {
            temp_fd = open(term_path, O_RDWR);
            if (temp_fd < 0)
                return (perror("minishell: setting fd"), errno);
            temp_fd = dup2(temp_fd, i);
            if (temp_fd < 0)
                return (perror("minishell: setting fd"), errno);
        }
        i++;
    }
    return (0);
}

int main(int ac, char **av, char **envp)
{
	char *p = NULL;
    char    *term = NULL;
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
    term = ttyname(1);
    if (!term)
        {return (perror("minishell:"), free_all(envp), errno);}
	while (1 && !s_exit)
    {
       // printf("term_path: %s\n", term);
		sigaction(SIGQUIT, &C_slash, NULL);
        sigaction(SIGINT, &C_c, NULL);
        if (set_default_fd(term))
            return (free_all(envp), errno);
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
