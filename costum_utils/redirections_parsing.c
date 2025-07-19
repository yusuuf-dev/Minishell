#include "../minishell.h"

static char	*charjoin(char *s1, char c)
{
	size_t	i;
	size_t	len;
	char	*ptr;

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

static  int found_redi(char c1, char c2)
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

static char *add_list_redi(t_data *data, int type)
{

}

static char *remv_add_redi(char *str, t_data *data, int type, int *index)
{
    char    *new_str;
    char    *fd_str;
    char    *name;
    char    q;
    size_t  i;

    i = index;
    fd_str = NULL;
    while (i > 0 && ft_isalnum(str[i - 1]))
    {                                       
        charjoin(fd_str,str[i - 1]);
        i--;
    }
    if (fd_str)
        new_str = ft_strldup(str,i + 1);
    else
        new_str = ft_strldup(str,index);
    q = 0;
    if (type <= 2)
        i = index + 1;
    else
        i = index + 2;
    while (str[i] == ' ')
        i++;
    while (str[i])
    {
        if (!q && str[i] == ' ')
            break;
        if (!q && (str[i] == '\'' || str[i] == '\"'))
            q = str[i];
        if (q && str[i] == q)
            q = 0;
        name = charjoin(name,str[i]);
        i++;
    }
    new_str = ft_strjoin(new_str,&str[i]);

}


int redirections_parsing(t_data *data)
{
    char        *str;
    char        *new;
    size_t      i;
    char        q;

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
        if (!q && found_redi(str[i],str[i + 1]))
        {
            str = remv_add_redi(str,data,found_redi(str[i],str[i + 1]),&i);
            q = 0;
            continue;
        }
    }
    
}
