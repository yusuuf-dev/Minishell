#include <stdio.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t flag;

void signal_handler(int signum)
{
	printf("the signal got unblocked\n");
	flag++;
}
void signal_handlerquit(int signum)
{

	flag = -1;
}

int main(void)
{
	struct sigaction handler;
	struct sigaction handlerq;
	sigset_t set;

	if (sigemptyset(&set) == -1)
		return (1);
	if (sigaddset(&set, SIGINT) == -1)
		return (1);
	
	handler.sa_handler = signal_handler;
	handlerq.sa_handler = signal_handlerquit;
	if (sigemptyset(&(handler.sa_mask)) == -1||sigemptyset(&(handlerq.sa_mask)) == -1)
		return (1);
	handlerq.sa_flags = 0;
	handler.sa_flags = 0;
	if (sigaction(SIGQUIT, &handlerq, NULL) == -1)
		return (printf("error setting signal handler\n"), 1);
	
	while (flag < 5)
	{
		if (sigaction(SIGINT, &handler, NULL) == -1)
			return (printf("error setting signal handler\n"), 1);
	}
		
	if (sigprocmask(SIG_BLOCK, &set, NULL) == -1)
		return (printf("error sigprocmask\n"), 1);
	while (flag != -1)
	{
		if (sigaction(SIGINT, &handler, NULL) == -1)
			return (printf("error setting signal handler\n"), 1);
	}
	if (sigprocmask(SIG_UNBLOCK, &set, NULL) == -1)
		return (printf("error sigprocmask\n"), 1);	

	while (1)
		;
	return (0);
}
