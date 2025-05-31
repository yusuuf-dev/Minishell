#include <unistd.h>
#include <stdio.h>

int main(void)
{

	sleep(3);
	close(0);
	sleep(3);
	return (0);
}
