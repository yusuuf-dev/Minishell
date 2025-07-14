#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	sig_handler(int sig_num)
{
	printf("got the signal\n");
}

int main(void)
{
//	sighandler_t handler = sig_handler;
//	sigaction_t = 
//	signal(SIGTERM, handler);
	struct sigaction act;
	act.sa_handler = sig_handler;
	sigemptyset(&(act.sa_mask));
//	sigaction(SIGTERM, &act, NULL);

	while (1)
	{
		sigaction(SIGQUIT, &act, NULL);
		sleep(1);
	}

}
