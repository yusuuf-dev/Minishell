#include <stdio.h>
#include <unistd.h>
#include <termios.h>


int main(void)
{
	struct termios test;

	printf("maroc_NCCS: %d, : %d\n", NCCS, CINTR);
	printf("test.c_cc[VEOF]: %d\n", test.c_cc[VEOF]);
//	return (0);
	if (tcgetattr(0, &test) == -1)
	{
		return (printf("error reading terminal attr\n"), 1);
	}
	for (int i = 0; i < NCCS; i++)
	{
		printf("test.c_cc[%d]: %d\n", i, test.c_cc[i]);
	}
	test.c_cc[0] = _POSIX_VDISABLE;
	test.c_cc[VEOF] = 0;
	test.c_cc[VQUIT] = 0;
	if (tcsetattr(0, TCSANOW, &test) == -1)
		return (printf("error changing terminal attr\n"), 1);
	for (int j = 0; j < NCCS; j++)
	{
		printf("test.c_cc[%d]: %d\n", j, test.c_cc[j]);
	}
}
