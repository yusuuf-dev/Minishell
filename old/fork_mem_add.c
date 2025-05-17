#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	pid_t child_pid;

	int i = 5;

	child_pid = fork();
	
	if (!child_pid)
	{

		printf("i_add before: %p, value: %d\n", &i, i);
		i++;
		printf("i_add after: %p, value: %d\n", &i, i);

		printf("child\n");
	}
	else
	{	
		sleep(1);
		printf("i_add before: %p, value: %d\n", &i, i);
		i = 1231231;
		printf("i_add after: %p, value: %d\n", &i, i);
		printf("parent\n");
	}
	return (0);
}
