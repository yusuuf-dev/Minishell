#include "../minishell.h"

void    ft_putstr(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}