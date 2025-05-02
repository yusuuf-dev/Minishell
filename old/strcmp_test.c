#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s1 = "ABC=something";
	char *s2 = "ABC1=somethingelse";
	printf("%d\n", strncmp(s1, s2, 4));
}
