#include "../minishell.h"

static int found_redi(char c1, char c2)
{
    if (c1 == '>' && c2 != '>')
        return (REDI_OUT);
    else if (c1 == '<' && c2 != '<')
        return (REDI_IN); // makes this return 0
    else if (c1 == '>' && c2 == '>')
        return (REDI_APPEND);
    else if (c1 == '<' && c2 == '<')
        return (REDI_HEREDOC);
    else
        return (-1); // and this returns - 1
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

    /*if (type == 4)
    {
        // this is for heredoc found it
        return;
    }*/
    new_redi = ft_calloc(sizeof(t_redi_lst));
    new_redi->redi_type = type;
    if (type == REDI_OUT || type == REDI_APPEND)
    {
        if (fd == -1)
            new_redi->fd = 1;
    //    new_redi->redi_out = 1;
    }
   /* if (type > 2)
        new_redi->is_append = 1;*/
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
    custom_split(name,data, 0, ' ');
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


static int check_ambiguous(t_data *data)
{
    t_redi_lst *tmp;

    tmp = data->redi_lst;
    while (tmp)
    {       
        if (tmp->file_name == NULL && tmp->redi_type != REDI_HEREDOC)
            return (1);
        tmp = tmp->next;
    }
    return (0);
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
        begin = i;
        while (i > 0 && str[i - 1] != ' ')
            i--;
        fd_str = ft_strldup(&str[i],begin - i);
    }
    fd = redi_atoi(fd_str);
    if (fd == -1)
        new_str = ft_strldup(str, index);
    else
        new_str = ft_strldup(str, i);
    q = 0;
    if (type == REDI_IN || type == REDI_OUT)
        i = index + 1;
    else
        i = index + 2;
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
    if (type != REDI_HEREDOC && check_ambiguous(data))
        return (new_str);
    name = parse_fd_name(name, data, type);
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
        if (!q && (found_redi(str[i], str[i + 1]) != -1)) // if we applied the above changes
        {                                         // we need to chanage this condition to  !q && found_redi(str[i], str[i + 1]) != -1
            str = remv_add_redi(str, data, found_redi(str[i], str[i + 1]), i);
            i = 0;
            q = 0;
            continue;
        }
        i++;
    }
    data->p_rdl = str;
}
