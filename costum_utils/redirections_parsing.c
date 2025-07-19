#include "../minishell.h"

static char *charjoin(char *s1, char c)
{
    size_t i;
    size_t len;
    char *ptr;

    if (!c)
        return (s1);
    len = ft_strlen(s1);
    ptr = ft_malloc((len + 2) * sizeof(char));
    i = 0;
    while (i < len)
    {
        ptr[i] = s1[i];
        i++;
    }
    ptr[i++] = c;
    ptr[i] = 0;
    return (ptr);
}

static int found_redi(char c1, char c2)
{
    if (c1 == '>' && c2 != '>')
        return (1);
    else if (c1 == '<' && c2 != '<')
        return (2);
    else if (c1 == '>' && c2 == '>')
        return (3);
    else if (c1 == '<' && c2 == '<')
        return (4);
    else
        return (0);
}

static void add_linkedlist(t_data *data, t_redi_lst *new)
{
    t_redi_lst *tmp;

    if (!data->redi_lst)
    {
        data->redi_lst = new;
        return;
    }
    tmp = data->redi_lst;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = new;
}

static void add_list_redi(t_data *data, int type, int fd, char *name)
{
    t_redi_lst *new_redi;

    if (type == 4)
    {
        // this is for heredoc found it
        return;
    }
    new_redi = ft_calloc(sizeof(t_redi_lst));
    if (type == 1)
    {
        if (fd == -1)
            new_redi->fd = 1;
        new_redi->redi_out = 1;
    }
    if (type > 2)
        new_redi->is_append = 1;
    if (fd != -1)
        new_redi->fd = fd;
    new_redi->file_name = name;
    add_linkedlist(data, new_redi);
}

static int redi_atoi(char *nptr)
{
    int i;
    long rslt;

    i = 0;
    rslt = 0;
    if (!nptr || !nptr[0])
    {
        return (-1);
    }
    while (nptr[i])
    {
        if (ft_isdigit(nptr[i]))
        {
            if (rslt > 2147483647)
                return (-1); // the return used to be '2';
            rslt = rslt * 10;
            rslt = rslt + (nptr[i] - 48);
        }
        else
            return (-1); // the return used to be '2';
        i++;
    }
    if (rslt > 2147483647)
    {
        return (-1);
    }
    return (rslt);
}

static char *remv_add_redi(char *str, t_data *data, int type, int index)
{
    char *new_str;
    char *fd_str;
    int fd;
    char *name;
    char q;
    size_t i;
    size_t begin;

    i = index;
    fd_str = NULL;
    if (i > 0 && ft_isalnum(str[i - 1]))
    {
        while (i > 0 && str[i - 1] != ' ')
        {
            fd_str = charjoin(fd_str, str[i - 1]);
            i--;
        }
    }
    fd = redi_atoi(fd_str);
    if (fd == -1)
        new_str = ft_strldup(str, index);
    else
    {
        new_str = ft_strldup(str, i);
        fd_str = NULL;
    }
    q = 0;
    if (type <= 2)
        i = index + 1;
    else
        i = index + 2;
    while (str[i] == ' ')
        i++;
    begin = i;
    while (str[i])
    {
        if (!q && str[i] == ' ')
            break;
        if (!q && (str[i] == '\'' || str[i] == '\"'))
            q = str[i];
        if (q && str[i] == q)
            q = 0;
        i++;
    }
    name = ft_strldup(&str[begin], i - begin);
    new_str = ft_strjoin(new_str, &str[i]);
    add_list_redi(data, type, fd, name);
    return (new_str);
}

void redirections_parsing(t_data *data)
{
    char *str;
    // char        *new;
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
        if (q && str[i] == q)
            q = 0;
        if (!q && found_redi(str[i], str[i + 1]))
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
