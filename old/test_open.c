#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int	main(void)
{
//	int fd_file;
//	char *temp = strdup("jailbreak");
	int fd_file = open("jailbreak", O_CREAT|O_RDWR|O_TRUNC, 00644);
	if (fd_file < 0)
		perror("open error");
//	fd_file = dup2(fd_file, 55);
//	if (fd_file < 0)
//		perror("open error");
//	if (write(fd_file, "I've done it in the ear before", strlen("I've done it in the ear before")) == -1)
//		perror("");
	fd_file = dup2(fd_file, 60);
	if (fd_file < 0)
		perror("open error");
	fd_file = dup2(1, 60);	
	if (fd_file < 0)
		perror("open error");
	if (write(60, "I've done it in the ear before\n", strlen("I've done it in the ear before\n")) == -1)
		perror("");
	//int fd_file = open("jailbreakff", O_RDWR, O_CREAT, S_IRWXU);
	if (write(1, "Reap what you saw\n", strlen("Reap what you saw\n")) == -1)
		perror("");
	if (fd_file < 0)
		perror("open error");
//	if (write(fd_file, "fd_file: something\n", strlen("fd_file: something\n")) == -1)
//		return (perror("fd_file write: "), 1);
}
