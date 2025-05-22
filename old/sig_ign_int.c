#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void signal_handler(int signum)
{
	write(1, "I won't quit\n", 13);
}

int main(void)
{
	__sighandler_t C_c_handler= signal_handler;

	//signal(SIGINT, C_c_handler);
	signal(SIGINT, SIG_IGN);

	while (1)
		;
}
