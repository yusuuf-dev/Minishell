#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main(void)
{
	char *error_str;
	close(99);
	error_str = strerror(errno);
	printf("strerror: %s\n", error_str);
}
