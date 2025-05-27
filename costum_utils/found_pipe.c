#include "../minishell.h"

static int check_out_quotes(char *p)
{
    size_t i = 0;
    char q = 0;

    while (p[i])
    {
        if (!q && (p[i] == '\"' || p[i] == '\''))
            q = p[i];
        else if (q && p[i] == q)
            q = 0;
        else if (!q && p[i] == '|')
            return (1);
        i++;
    }
    return (0);
}

static int check_double_pip(char *p)
{
    size_t i = 0;
    char q = 0;

    while (p[i] == ' ')
        i++;
    if (p[i] == '|')
        return (0);
    i = ft_strlen(p) - 1;
    while (p[i] == ' ')
        i--;
    if (p[i] == '|')
        return(0);
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
            while (p[i] == ' ')
                i++;
            if (p[i] == '|')
                return(0);
            i--;
        }
        i++;
    }
    return (1);
}

int     check_valid_char(char *p)
{
    size_t  i = 0;
    char    q = 0;
    int     f = 0;
    int     count = 0;

    while (p[i])
    {
        if (!q && !f && (p[i] == '<' || p[i] == '>'))
            f = 1;
        else if (p[i] == '|' && f)
            return(0);
        else if (f && p[i] != ' ' && p[i] != '<' && p[i] != '>')
            f = 0;
        else if (!q && (p[i] == '\'' || p[i] == '\"'))
            q = p[i];
        else if (q && p[i] == q)
            q = 0;
        i++;
    }
    return(1);
}

int found_pipe(char *line)
{
    if (!check_out_quotes(line))
        return (0);
    if (!check_double_pip(line))
        return (-1);
    if (!check_valid_char(line))
        return (-1);
    return (1);
}
