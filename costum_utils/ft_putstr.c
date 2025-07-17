#include "../minishell.h"

void    ft_putstr(char *s, int fd)
{
    if (!s)
        return;
    write(fd, s, ft_strlen(s));
}