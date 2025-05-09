#include "../minishell.h"

int     found_pipe(char *line,char **envp)
{
    size_t  i;
    size_t  j;
    char **segments;

    segments = ft_split(line, ' ');
    if (!segments)
        return(-1); // protect malloc error
    i = 0;
    while (segments[i])
    {
        j = 0;
        if (segments[i][0] == '|')
            return(free_all(segments),1);
        while (segments[i][j])
        {
            j++;
            if (j > 0 && !segments[i][j] && segments[i][j - 1] == '|')
                return(free_all(segments),1);
        }
        if (ft_strcmp(segments[i],"|"))
            return(free_all(segments),1);
        i++;
    }
    free_all(segments);
    return(0);
}
