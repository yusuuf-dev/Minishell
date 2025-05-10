#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **envp)
{

	printf("TEST: %s\n", getenv("TEST"));
	printf("first var_env: %s\n", envp[0]);

}
