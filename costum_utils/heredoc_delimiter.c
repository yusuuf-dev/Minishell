#include "../minishell.h"

static size_t get_delimiter_end(char *s, int *isquote)
{
    size_t i = 2;
    char q = 0;

    while (s[i] == ' ')
        i++;
    while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>' && s[i] != '|')
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
    return (i);
}

static void copy_delimiter(char *dst, char *src, size_t start, size_t end)
{
    char q = 0;
    size_t j = 0;

    while (start < end)
    {
        if (!q && src[start] == '$' && src[start + 1] == '$')
            dst[j++] = src[start++];
        if (!q && (src[start] == '\'' || src[start] == '\"'))
            q = src[start];
        else if (q && src[start] == q)
            q = 0;
        else if (!q || (q && src[start] != q))
            dst[j++] = src[start];
        start++;
    }
    dst[j] = '\0';
}

char *heredoc_old_delimiter(char *s, int *isquote, int *index_ret)
{
    size_t start;
    size_t end;
    char *delimiter;

    while (s[2] == ' ')
        s++;
    start = 2;
    end = get_delimiter_end(s, isquote);
    *index_ret = end;
    delimiter = ft_malloc(end - start + 1);
    copy_delimiter(delimiter, s, start, end);
    return (delimiter);
}

// char    *heredoc_old_delimiter(char *s ,int *isquote, int *index_ret)
// {
//     size_t i = 0;
//     size_t st = 0;
//     size_t j = 0;
//     char q = 0;
//     char *delimiter;

//     i = 2;
//     while (s[i] == ' ')
//         i++;
//     st = i;
//     while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
//     {
//         if (!q && (s[i] == '\'' || s[i] == '\"'))
//         {
//             q = s[i++];
//             *isquote = 1;
//         }
//         while (q && s[i] != q)
//             i++;
//         q = 0;
//         i++;
//     }
//     *index_ret = i;
//     delimiter = malloc((i - st + 1) * sizeof(char));
//     if (!delimiter)
//         return (NULL);
//     while (s[st] && st < i)
//     {
//         if (!q && s[st] == '$' && s[st + 1] == '$')
//         {
//             delimiter[j++] = s[st++];
//             delimiter[j++] = s[st];
//         } 
//         else if (!q && s[st] == '$' && s[st + 1] != '\"' && s[st + 1] != '\'')
//             delimiter[j++] = s[st];
//         else if (!q && (s[st] == '\'' || s[st] == '\"'))
//             q = s[st];
//         else if (q && s[st] == q)
//             q = 0;
//         else if (q)
//             delimiter[j++] = s[st];
//         else if (!q && s[st] != '$')
//             delimiter[j++] = s[st];
//         st++;
//     }
//     delimiter[j] = 0;
//     return (delimiter);
// }

