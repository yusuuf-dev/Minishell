#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char buffer[1024];

	int read_ret = read(0, buffer, 1024);
	if (read_ret < 0)
		return (printf("Error while reading\n"), 1);
	buffer[read_ret] = 0;

	write(1, buffer, strlen(buffer));
}
