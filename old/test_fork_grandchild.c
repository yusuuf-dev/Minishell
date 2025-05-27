#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(void)
{
	int child_1 = 0;
	int child_2 = 0;
	int child_3 = 0;
	int child_status = 0;
	char	*s = calloc(1024, 1);

	strcpy(s, "This must be the place");
	child_1 = fork();
	if (child_1 < 0)
		return (printf("Error forking\n"), 1);
	if (child_1 == 0)
	{
		printf("The first child is up and running\n");
		int f = open("test_file_123123.txt", O_RDWR | O_CREAT, 0666);
		child_2 = fork();
		if (child_2 < 0)
			return (printf("Error child counl't fork\n"), 1);
		if (child_2 == 0)
		{
			printf("child_s: %s\n", s);
			printf("the grand child is up\n");
			write(f, "nay", 3);
//			sleep(3); 
			free(s);
			if (unlink("test_file_123123.txt") == - 1)
				return (printf("unlink: error_num: %d\n", errno), 1);
			return (0);
		}
		else
		{
			printf("grand_child_s: %s\n", s);
			while (wait(NULL) != -1)
        			;
			printf("the grandchild exited\n");
//			sleep(3);
			printf("grand_child_s: %s\n", s);
			char buffer[1024];
/*			if ((read(f, buffer, 3)) != 3)
				return (printf("Error while reading, errno: %d\n", errno), 1);*/
			printf("I with the pid: %d, wrote: %ld, to fd: %d\n", getpid(), write(f, "aye", 3), f);
//				return (printf("Error while writing\n"), 1);
//			buffer[3] = 0;
//			printf("read: %s\n", buffer);
			sleep(10);
			return (0);
		}
	}
	else
	{
		sleep(3);
		waitpid(child_1, &child_status, 0);
		printf("The parent is not in waiting state anymore\n");
	}
}
