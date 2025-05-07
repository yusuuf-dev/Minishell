#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
	int i = 0;
	int pid = 0;

	while (i < 62019)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("");
			exit(errno);
		}
		if (!pid)
		{
			sleep(60);
			printf("child_num: %d\n", i);
		}
		else
			i++;
	}
}
