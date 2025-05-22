#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
	int i = 0;

	i = access("/home/asoufian", X_OK);

	printf("i: %d, errno: %d\n", i, errno);
}
