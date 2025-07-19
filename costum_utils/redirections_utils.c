
#include "../minishell.h"

static int    open_create_file_name(t_redi_lst *redis, int *file_fd)
{
    char    *error_print;

    if (redis->redi_out == 0)
    {
        *file_fd = open(redis->file_name, O_RDONLY, 00644);
    }
    else
    {
        if (redis->is_append)
            *file_fd = open(redis->file_name, O_WRONLY|O_CREAT|O_APPEND, 00644);
        else
            *file_fd = open(redis->file_name, O_WRONLY|O_CREAT|O_TRUNC, 00644);
    }
    if (*file_fd < 0)
    {
        error_print = ft_strjoin("minishell: ", redis->file_name);
        error_print = ft_strjoinf(error_print, ": ");
        error_print = ft_strjoinf(error_print, strerror(errno));
        error_print = ft_strjoinf(error_print, "\n");
        ft_putstr(error_print, 2);
        return (1);
    }
    return (0);
}
/* dups the fd of the file_name arg to the fd that the user enter
    if any, otherwise we use the default fds 0 for stdin, 1 for stdout */
static int    redirect_to_file(t_redi_lst *redis, int *file_fd)
{
    char    *error_print;

    redis->fd = dup2(*file_fd, redis->fd);
    close(*file_fd);
    if (redis->fd < 0)
    {
        error_print = ft_strjoin("minishell: ", ft_itoa(redis->fd));
        error_print = ft_strjoinf(error_print, " ");
        error_print = ft_strjoinf(error_print, strerror(errno));
        error_print = ft_strjoinf(error_print, "\n");
        ft_putstr(error_print, 2);
        return (1);
    }
     return (0);
}

int    ft_redis_execute(t_data *data)
{
    t_redi_lst    *temp = data->redi_lst;
    int        file_fd;

    if (!temp)
        return (0);
    while (temp)
    {
        if (!temp->file_name)
            return (data->status = 1, 1);
        if (open_create_file_name(temp, &file_fd))
            return (data->status = 1, 1);
        if (redirect_to_file(temp, &file_fd))
            return (data->status = 1, 1);
        temp = temp->next;
    }
    return (0);
}
