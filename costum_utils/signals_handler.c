#include "../minishell.h"

volatile sig_atomic_t f_sig = 0;

void    signal_handler(int signum)
{
	(void)signum;
  //  status = 130;
  //  write(1, "here\n", 5);
    if (f_sig != 2)
    {
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
    else
        write(1, "\n", 1);
    f_sig = 1;
}

void    count_sigs(int signum)
{
    (void)signum;
    f_sig = 2;
}