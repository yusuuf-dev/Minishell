#include "../minishell.h"

char    *heredoc_delimiter(char *s)
{
    size_t i = 0;
    size_t st = 0;
    size_t f = 0;
    size_t j = 0;
    char    *delimiter;

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
                i++;
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
    return(delimiter);
}
   