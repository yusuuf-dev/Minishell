#include "../minishell.h"

char    *heredoc_delimiter(char *s ,int *isquote)
{
    size_t  i;
    size_t  j;
    char    *delimiter;

    i = 0;
    if (s[i] == '\'' || s[i] == '\"')
        *isquote = 1;
    while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
        i++;
    delimiter = malloc((i + 1) * sizeof(char));
    if (!delimiter)
        return(NULL);
    j = 0;
    while (j < i)
    {
        delimiter[j] = s[j];
        j++;
    }
    delimiter[j] = 0;
    delimiter = rm_quotes(delimiter);
    if (!delimiter)
        return (NULL);
    return(delimiter);
}
   