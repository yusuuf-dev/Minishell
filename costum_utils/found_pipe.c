#include "../minishell.h"

int     found_pipe(char *line,char **envp)
{
    int  i;
    char **segments;

    segments = c_split(line, ' ',envp);
    if (!segments)
        return(-1); // protect malloc error
    i = 0;
    while (segments[i])
    {
        // if (ft_strncmp(segments[i], "||",2))
        // {
        //     free_all(segments);
        //     return(2);
        // }
        if (ft_strcmp(segments[i],"|"))
        {
            free_all(segments);
            return(1);
        }
        i++;
    }
    free_all(segments);
    return(0);
}