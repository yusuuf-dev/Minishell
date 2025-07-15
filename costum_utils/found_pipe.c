#include "../minishell.h"

int found_pipe(char *line)
{
    size_t  i;
    char    q;

    i = 0;
    q = 0;
    while (line[i])
    {
        if (!q && (line[i] == '\'' || line[i] == '\"'))
            q = line[i];
        else if (line[i] == q)
            q = 0;
        else if (!q && line[i] == '|')
            return (1);
        i++;
    }
    return (0);
}
