#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("exist: %d\n", access("/usr/bin/echo", F_OK));
	printf("exist: %d\n", access("/usr/bin/echo", X_OK));
	printf("exist: %d\n", access("/usr/bin/echo", W_OK));


}
