#include "../minishell.h"

#include "../minishell.h"

char    *heredoc_old_delimiter(char *s ,int *isquote, int *index_ret)
{
    size_t i = 0;
    size_t st = 0;
    size_t f = 0;
    size_t j = 0;
    char q = 0;
    char *delimiter;

    i = 2;
    f = 0;
    while (s[i] == ' ')
        i++;
    st = i;
    while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
    {
        if (!q && (s[i] == '\'' || s[i] == '\"'))
        {
            q = s[i++];
            *isquote = 1;
        }
        while (q && s[i] != q)
            i++;
        q = 0;
        i++;
    }
    *index_ret = i;
    delimiter = malloc((i - st + 1) * sizeof(char));
    if (!delimiter)
        return (NULL);
    while (s[st] && st < i)
    {
        if (!q && s[st] == '$' && s[st + 1] == '$')
        {
            delimiter[j++] = s[st++];
            delimiter[j++] = s[st];
        } 
        else if (!q && s[st] == '$' && s[st + 1] != '\"' && s[st + 1] != '\'')
            delimiter[j++] = s[st];
        else if (!q && (s[st] == '\'' || s[st] == '\"'))
            q = s[st];
        else if (q && s[st] == q)
            q = 0;
        else if (q)
            delimiter[j++] = s[st];
        else if (!q && s[st] != '$')
            delimiter[j++] = s[st];
        st++;
    }
    delimiter[j] = 0;
    return (delimiter);
}
/*char    *heredoc_old_delimiter(char *s ,int *isquote, int *index_ret)
{
    size_t i = 0;
    size_t st = 0;
    size_t f = 0;
    size_t j = 0;
    char    q = 0;
    char    *delimiter;
    char    *tmp;

    i = 2;
    f = 0;

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
    *index_ret = i; // this is to indicate where the delimiter ends, so I can resume searching based on it;
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
    tmp = delimiter;
    delimiter = rm_quotes(delimiter);
    if (!delimiter)
        return (NULL);
    free(tmp);    
    return(delimiter);
}*/
/*char    *heredoc_delimiter(char *s ,int *isquote)
{
    size_t i = 0;
    size_t st = 0;
    size_t f = 0;
    size_t j = 0;
    char    q = 0;
    char    *delimiter;
    char    *tmp;

    i = 2;
    f = 0;

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
}*/
   