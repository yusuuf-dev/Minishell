
#include "../minishell.h"

int     found_heredoc(char *s)
{
    size_t i = 0;
    size_t j = 0;
    char    q = 0;

    while (s[i])
    {
        if (!q && (s[i] == '\"' || s[i] == '\''))
            q = s[i];
        else if (!q && s[i] == '<' && s[i + 1] ==  '<')
        {
            if (!s[i + 2] || s[i + 2] == '<' || s[i + 2] == '>')
                return(-1);
            else
                return(1);
        }
        else if (s[i] == q)
            q = 0;
        i++;
    }
    return(0);
}