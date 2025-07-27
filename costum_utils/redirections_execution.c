<<<<<<< HEAD

#include "../minishell.h"

/*int found_here_doc(t_data *data, char *s)
{
	t_heredoc	*temp = data->heredooc;
	int			fd;
	while(temp->next && temp->arg_num)
	{
		temp = temp->next;
	}

	fd = open(temp->file_name, O_RDONLY);
	if (fd < 0)
		return (perror(""), errno);
	if (dup2(fd, 0) < 0)
		{return (close(fd), perror(""), errno);}
	close(fd);
	temp->arg_num = 1;
	remove_heredoc(s);
	return (0);
}*/

static void    *get_here_doc_file(t_data *data)
{
    t_heredoc   *temp;

    temp = data->heredooc;
    if (!temp)
        {return (NULL);}
	while(temp->next && temp->taken)
	{
		temp = temp->next;
	}
    temp->taken = 1;
    return (temp->file_name);
}

static int    open_create_file_name(t_data *data, t_redi_lst *redis, int *file_fd)
{
    char    *error_print;

    if (redis->redi_type == REDI_HEREDOC)
        *file_fd = open(get_here_doc_file(data), O_RDONLY, 00644);
    else if (redis->redi_type == REDI_IN)
    {
        *file_fd = open(redis->file_name, O_RDONLY, 00644);
    }
    else
    {
        if (redis->redi_type == REDI_APPEND)
            *file_fd = open(redis->file_name, O_WRONLY|O_CREAT|O_APPEND, 00644);
        else
            *file_fd = open(redis->file_name, O_WRONLY|O_CREAT|O_TRUNC, 00644);
    }
    if (*file_fd < 0)
    {
        error_print = ft_strjoin("minishell: ", redis->file_name);
        error_print = ft_strjoin(error_print, ": ");
        error_print = ft_strjoin(error_print, strerror(errno));
        error_print = ft_strjoin(error_print, "\n");
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
        error_print = ft_strjoin(error_print, " ");
        error_print = ft_strjoin(error_print, strerror(errno));
        error_print = ft_strjoin(error_print, "\n");
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
        if (!temp->file_name && temp->redi_type != REDI_HEREDOC)
            return (ft_putstr(data->ptr_ambiguous, 2), data->status = 1, 1);
        if (open_create_file_name(data, temp, &file_fd))
            return (data->status = 1, 1);
        if (redirect_to_file(temp, &file_fd))
            return (data->status = 1, 1);
        temp = temp->next;
    }
    return (0);
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_execution.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 10:42:13 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 10:49:11 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error(char *s)
{
	char	*error_print;

	error_print = ft_strjoin("minishell: ", s);
	error_print = ft_strjoin(error_print, ": ");
	error_print = ft_strjoin(error_print, strerror(errno));
	error_print = ft_strjoin(error_print, "\n");
	ft_putstr(error_print, 2);
}

static void	*get_here_doc_file(t_data *data)
{
	t_heredoc	*temp;

	temp = data->heredooc;
	if (!temp)
	{
		return (NULL);
	}
	while (temp->next && temp->taken)
	{
		temp = temp->next;
	}
	temp->taken = 1;
	return (temp->file_name);
}

static int	open_create_file_name(t_data *data, t_redi_lst *redis, int *file_fd)
{
	char	*file_name;

	file_name = redis->file_name;
	if (redis->redi_type == REDI_HEREDOC)
		*file_fd = open(get_here_doc_file(data), O_RDONLY, 00644);
	else if (redis->redi_type == REDI_IN)
	{
		*file_fd = open(file_name, O_RDONLY, 00644);
	}
	else
	{
		if (redis->redi_type == REDI_APPEND)
			*file_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 00644);
		else
			*file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	}
	if (*file_fd < 0)
	{
		print_error(file_name);
		return (1);
	}
	return (0);
}

/* dups the fd of the file_name arg to the fd that the user enter
	if any, otherwise we use the default fds 0 for stdin, 1 for stdout */
static int	redirect_to_file(t_redi_lst *redis, int *file_fd)
{
	char	*error_print;

	redis->fd = dup2(*file_fd, redis->fd);
	close(*file_fd);
	if (redis->fd < 0)
	{
		error_print = ft_strjoin("minishell: ", ft_itoa(redis->fd));
		error_print = ft_strjoin(error_print, " ");
		error_print = ft_strjoin(error_print, strerror(errno));
		error_print = ft_strjoin(error_print, "\n");
		ft_putstr(error_print, 2);
		return (1);
	}
	return (0);
}

int	ft_redis_execute(t_data *data)
{
	t_redi_lst	*temp;
	int			file_fd;

	temp = data->redi_lst;
	if (!temp)
		return (0);
	while (temp)
	{
		if (!temp->file_name && temp->redi_type != REDI_HEREDOC)
			return (ft_putstr(data->ptr_ambiguous, 2), data->status = 1, 1);
		if (open_create_file_name(data, temp, &file_fd))
			return (data->status = 1, 1);
		if (redirect_to_file(temp, &file_fd))
			return (data->status = 1, 1);
		temp = temp->next;
	}
	return (0);
>>>>>>> 40ab6a92f5ee8ea4ead42ea65eb919d4bac9e369
}
