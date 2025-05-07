#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	for(int i = 1;i < 2025;i++)
	{
		printf("%d>a%d ", i, i);
	}
	return (0);
}
