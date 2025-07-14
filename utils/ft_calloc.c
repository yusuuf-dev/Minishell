#include "../minishell.h"

void    *ft_calloc(size_t n)
{
    char    *p;

    p = ft_malloc(n);
    n--;
    while(n)
    {
        p[n] = 0;
        n--;
    }
    p[n] = 0;
    return (p);
}
// void *allocater(int type, int size, ...)
// {

// }