#include "../minishell.h"

void *ft_malloc(size_t size)
{
    void *p;

    p = malloc(size);
    if (!p)
        config_malloc(NULL,1,0);
    else
    {
        config_malloc(p, 0,0);
    }
    return (p);
}

void *ft_malloc_env(size_t size)
{
    void *p;

    p = malloc(size);
    if (!p)
        config_malloc(NULL,1,1);
    else
    {
        config_malloc(p, 0, 1);
    }
    return (p);
}
