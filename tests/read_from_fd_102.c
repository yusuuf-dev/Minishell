#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char	buffer[1000000];
	int	i = 0;
	while (read(102, &buffer[i], 1) != 0)
	{
		i++;
	}
	buffer[i] = 0;
	printf("%s\n", buffer);
}
