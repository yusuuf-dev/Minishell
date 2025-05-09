#include "../minishell.h"

static int check_out_quotes(char *p)
{
    size_t i = 0;
    char    q = 0; 

    while (p[i])
    {
        if (!q && (p[i] == '\"' || p[i] == '\''))
            q = p[i];
        else if (q && p[i] == q)
            q = 0;
        else if (!q && p[i] == '|')
            return(1);
        i++;
    }
    return (0);
}

static int check_error_pip(char *p)
{
    size_t i = 0;
    char    q = 0; 
    int     is_pip = 0;

    if (p[0] == '|')
        return(0);
    while (p[i] == ' ')
    {
        if (p[i] == '|')
            return(0);
        i++;
    }
    i = ft_strlen(p) - 1;
    while (p[i] == ' ')
    {
        if (p[i] == '|')
            return(0);
        i--;
    }
    i = 0;
    while (p[i])
    {
        if (!q && (p[i] == '\"' || p[i] == '\''))
            q = p[i];
        else if (q && p[i] == q)
            q = 0;
        else if (!q && p[i] == '|')
        {
            i++;
            if (p[i] == '|')
                return(0);
            while (p[i] == ' ')
            {
                if (p[i] == '|')
                    return(0)
                i++;
            }
            i--;
        }
        i++;
    }
    return (1);
}


int     found_pipe(char *line,char **envp)
{

    if (!check_out_quotes(line))
        return (0);
    if (!check_error_pip(line))
        return (0);
    return(1);
}
