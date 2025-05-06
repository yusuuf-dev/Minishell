#include "../minishell.h"

char    *heredoc_delimiter(char *s ,int *isquote)
{
    size_t i = 0;
    size_t st = 0;
    size_t f = 0;
    size_t j = 0;
    char    q = 0;
    char    *delimiter;
    char    *tmp;

    while (s[i])
    {
        if (i > 0 && s[i - 1] == '<' && s[i] == '<')
        {
            f = i - 1;
            i++;
            while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
                i++;
            st = i;
            while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
            {
                if (!q && (s[i] == '\'' || s[i] == '\"'))
                {
                    q = s[i++];
                    *isquote = 1;
                }
                while(q && s[i] != q)
                    i++;
                q = 0;
                i++;
            }
            break;
        }
        i++;
    }
    delimiter = malloc((i - st + 1) * sizeof(char));
    if (!delimiter)
        return (NULL);
    while (st + j < i)
    {
        delimiter[j] = s[st + j];
        j++;
    }
    delimiter[j] = 0;
    j = 0;
    while (s[i])
    {
        s[f + j] = s[i];
        j++;
        i++;
    }
    s[f + j] = 0;
    tmp = delimiter;
    delimiter = rm_quotes(delimiter);
    if (!delimiter)
        return (NULL);
    free(tmp);    
    return(delimiter);
}
   