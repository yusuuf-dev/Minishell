#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **ag, char **envp)
{

    char **p = malloc(sizeof(char *) * 3);
    p[0] = strdup("/usr/bin/ls");
    p[1] = NULL;
  //  char *p[] = {"/usr/bin/ls", "NULL"};
  //  char *p2[] = {"ls", "NULL"};
    execve(p[0], p, NULL);
    printf("error execve errno: %d\n", errno);
}