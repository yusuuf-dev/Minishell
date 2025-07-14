#include "../minishell.h"

int signal_fun(int n)
{
    static volatile sig_atomic_t sig;

    if (n == -1)
        return (sig);
    sig = n;
    return (0);
}

void    signal_handler(int signum)
{
	(void)signum;

    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
    signal_fun(1);
}


/*extern volatile sig_atomic_t f_sig;

void setup(t_data *data)
{
	struct sigaction C_slash;
    struct sigaction C_c;
    sigemptyset(&(C_slash.sa_mask));
    sigemptyset(&(C_c.sa_mask));
    C_slash.sa_flags = 0; // change me to SA_RESTART
    C_c.sa_flags = 0;
    C_slash.sa_handler = SIG_IGN;
   // C_slash.sa_handler = ignoree;
    C_c.sa_handler = signal_handler;



    struct sigaction C_c_alt;
	struct sigaction old_C_c;
	sigemptyset(&(C_c_alt.sa_mask));
	C_c_alt.sa_flags = SA_RESTART; // change me to SA_RESTART
    C_c_alt.sa_handler = count_sigs;
}*/