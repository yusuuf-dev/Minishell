#include "../minishell.h"

static void free_malloc_exit(t_lstm *lst, int is_exit)
{
    t_lstm *tmp;

    while (lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->p);
        free(tmp);
    }
    if (is_exit)
    {
        write(2,"failed malloc\n",14);
        exit(1);
    }
}

static t_lstm *last_node(t_lstm *lst)
{
    t_lstm  *last;

    last = lst;
    while (last->next)
    {
        last = last->next;
    }
    return(last);
}

static void failed_first_malloc(char *ptr)
{
    free(ptr);
    write(2,"failed malloc\n",14);
    exit(1);
}

void config_malloc(void *ptr, int isfailed)
{
    static t_lstm *lstmalloc = NULL;
    t_lstm *tmp;
    t_lstm *new_malloc;

    if (ptr)
    {
        new_malloc = malloc(sizeof(t_lstm));
        if (!new_malloc && !lstmalloc)
            failed_first_malloc(ptr);
        else if (!new_malloc && lstmalloc)
            free_malloc_exit(lstmalloc,1);
        new_malloc->p = ptr;
        new_malloc->next = NULL;
        if (!lstmalloc)
        {
            lstmalloc = new_malloc;
            return;
        }
        tmp = last_node(lstmalloc);
        tmp->next = new_malloc;
    }
    else if (!ptr && isfailed)
        free_malloc_exit(lstmalloc,1);
    else
        free_malloc_exit(lstmalloc,0);
}

void *ft_malloc(size_t size)
{
    static int is_malloced = 0;
    void *p;

    p = malloc(size);
    if (!p && !is_malloced)
    {
        write(2,"failed malloc\n",14);
        exit(1);
    }
    else if (!p && is_malloced)
        config_malloc(NULL,1);
    else
    {
        config_malloc(p,0);
        is_malloced = 1;
    }
    return (p);
}

