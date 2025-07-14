#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void	sig_handler(int sig_num)
{
	printf("got the signal\n");
	exit(131);
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
		sigaction(SIGINT, &act, NULL);
		sleep(1);
	}

}
