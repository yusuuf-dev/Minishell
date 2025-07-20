#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char *s1 = "this is written in fd 4\n";
	char *s2 = "this is written in fd 2\n";
	char *s3 = "this is written in fd 1\n";

	write(4, s1, strlen(s1));
	write(2, s2, strlen(s2));
	write(1, s3, strlen(s3));
}
