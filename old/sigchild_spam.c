#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int pid = atoi(argv[1]);
	while (1)
	{
		if (kill(pid, SIGCHLD) == -1)
		{
			printf("error kill\n");
			exit (-1);
		}
		else
			printf("sent signal\n");

	}
	return (0);
}
