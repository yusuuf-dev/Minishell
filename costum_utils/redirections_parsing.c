/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_parsing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:23:49 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/23 11:52:28 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *parse_fd_name(char *name, t_data *data, int type)
{
    char    **ptrs;
    char    *error;
    int     check;

    if (type == REDI_HEREDOC)
        return (NULL);
    data->rdl_args = NULL;
    check = found_quotes(name);
    if (check == 0)
        return ("");
    custom_split(name,data, 0,0);
    ptrs = data->rdl_args;
    if (!ptrs && check > 1)
        return ("");
    if (!ptrs || (ptrs[0] && ptrs[1]))
    {
        error = ft_strjoin("minishell: ",name);
        error = ft_strjoin(error,": ambiguous redirect\n");
        data->ptr_ambiguous = error;
        return (data->status = 1, NULL);
    }
    else
        return (ptrs[0]);
}

static char *is_fd_redirection(char *str, size_t *i, int *fd, int type)
{
    size_t  begin;
    size_t  save_i;
    char    *new_str;
    char    *fd_str;

    fd_str = NULL;
    save_i = *i;
    if(*i > 0 && ft_isalnum(str[*i -1]))
    {
        begin = *i;
        while (*i > 0 && str[*i - 1] != ' ')
            (*i)--;
        fd_str = ft_strldup(&str[*i],begin - *i);
    }
    *fd = redi_atoi(fd_str);
    if (*fd == -1)
        new_str = ft_strldup(str, save_i);
    else
        new_str = ft_strldup(str, *i);
    if (type == REDI_IN || type == REDI_OUT)
        *i = save_i + 1;
    else
        *i = save_i + 2;
    return (new_str);
}

static void check_status_add(t_data *data, char *name, int type, int fd)
{
    if (type != REDI_HEREDOC && check_ambiguous(data))
        return ;
    else
    {
        name = parse_fd_name(name, data, type);
        add_list_redi(data, type, fd, name);
    }
}

static char *remv_add_redi(char *str, t_data *data, int type, size_t i)
{
    char *new_str;
    int fd;
    char *name;
    char q;
    size_t begin;

    new_str = is_fd_redirection(str,&i,&fd,type);
    q = 0;
    while (str[i] == ' ')
        i++;
    begin = i;
    while (str[i])
    {
        if (!q && (str[i] == ' ' || found_redi(str[i],str[i + 1]) != -1))
            break;
        if (!q && (str[i] == '\'' || str[i] == '\"'))
            q = str[i];
        else if (q && str[i] == q)
            q = 0;
        i++;
    }
    name = ft_strldup(&str[begin], i - begin);
    new_str = ft_strjoin(new_str, &str[i]);
    check_status_add(data,name,type,fd);
    return (new_str);
}

void redirections_parsing(t_data *data)
{
    char *str;
    size_t i;
    char q;

    i = 0;
    q = 0;
    str = data->p_rdl;
    data->redi_lst = NULL;
    while (str[i])
    {
        if (!q && (str[i] == '\'' || str[i] == '\"'))
            q = str[i];
        else if (q && str[i] == q)
            q = 0;
        if (!q && (found_redi(str[i], str[i + 1]) != -1))
        {                                     
            str = remv_add_redi(str, data, found_redi(str[i], str[i + 1]), i);
            i = 0;
            q = 0;
            continue;
        }
        i++;
    }
    data->p_rdl = str;
}
