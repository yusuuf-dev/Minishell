#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	int fd = open("../file.txt", O_RDONLY);

	if (fd == -1)
		return ("Error while opening the file\n", -1);
	
	char s[100];
	char p[100];
	int cpid;
	cpid = fork();
	if (cpid == -1)
		return (printf("Error while forking\n"), -1);
	if (!cpid) // child
	{
		int read_out = read(fd, s, 10);
		s[read_out] = 0;
		printf("the read from the child: %s\n", s);
		return (0);
	}
	else // parent
	{
		wait(NULL);
		int read_out = read(fd, p, 10);
		p[read_out] = 0;
		printf("the read from the parent: %s\n", p);
	}
	return (0);
}
