#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char buffer[1024];
	int fd = open("test.txt", O_RDWR);
	if (fd == -1)
		return (printf("error opening\n"), 1);
	int read_count = read(fd, buffer, 10);
	if (read_count == -1)
		return (printf("error while reading\n"), 1);
	printf("before forking string: %s\n", buffer);
	pid_t child_pid = fork();
	if (child_pid == -1)
		return (printf("Error while forking\n"), 1);
	if (!child_pid)
	{ // child

		close(fd);
	}
	else
	{ // parent
		read_count = read(fd, buffer, 10);
		if (read_count == -1)
			return (printf("error while reading\n"), 1);
		buffer[read_count] = 0;
		printf("after forking string: %s\n", buffer);
	}
	return (0);
}
