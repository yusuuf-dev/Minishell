#include "../minishell.h"

void *ft_memset(void *ptr, int c, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        ((unsigned char*)ptr)[i] = c;
        i++;
    }
    return (ptr);
}