#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(void)
{
/*	char **p[2];*/
	char *p[] = {"/home/asoufian/minishell/minishell", NULL};
/*	p[0] = "/usr/bin/bash";
	p[1] = NULL;*/
//	char *p1 = "/usr/bin/bash";
	signal(SIGQUIT, SIG_IGN);
//	execve("/usr/bin/bash", {"/usr/bin/bash", NULL}, __environ);
	execve(p[0], p, __environ);
	printf("error execve\n");
}
