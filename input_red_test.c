#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char	*read_buf = malloc(sizeof(char) * 24);
	int	c_read = 0;
	c_read = read(44, read_buf, 20);
	if (c_read < 0)
		return (printf("Error while reading\n"), -1);
	read_buf[c_read] = 0;
	printf("the read string is: %s", read_buf);
}
