#include "../minishell.h"

static int check_next(char *p, int index ,int isdouble)
{
    int i;
    if (isdouble)
        i = index + 2;
    else
        i = index + 1;
    while (p[i] && p[i] == ' ')
        i++;
    if (p[index] == '|' && (!p[i] || p[i] == '|'))
        return(ft_putstr("Minishell: syntax error\n",2),1);
    if (p[index] == '|')
        return(0);
    if(!p[i] || p[i] == '<' || p[i] == '>' || p[i] == '|')
        return(ft_putstr("Minishell: syntax error\n",2),1);
    return(0);       
}

static void ft_space(char *p)
{
    int     i;
    char    q;

    i = 0;
    q = 0;
    while (p[i])
    {
        if (!q && (p[i] == '\'' || p[i] == '\"'))
            q = p[i];
        else if (q && p[i] == q)
            q = 0;
        else if (p[i] >= 9 && p[i] <= 13)
            p[i] = ' ';
        i++;
    }
}

static int is_onlyspace(char *p)
{
    int     i;

    ft_space(p);
    i = 0;
    while (p[i])
    {
        if (p[i] != ' ')
            return(0);
        i++;
    }
    return(1);
}


int     check_syntax(char *p)
{
    int  i;
    char    q;

    if(found_q(p) == -1)
        return(ft_putstr("Error Unclose quote\n",2),1);
    if (is_onlyspace(p))
        return(1);
    i = 0;
    q = 0;
    while (p[i] == ' ')
        i++;
    if (p[i] == '|')
        return(ft_putstr("Minishell: syntax error\n",2),1);
    while (p[i])
    {
        if (!q && (p[i] == '\'' || p[i] == '\"'))
            q = p[i];
        else if (q && p[i] == q)
            q = 0;
        else if (!q && p[i] == '|' && check_next(p,i,0))
            return(1);
        else if (!q && p[i] == '>' && p[i + 1] == '>' && check_next(p,i,1))
            return(1);
        else if (!q && p[i] == '<' && p[i + 1] == '<' && check_next(p,i,1))
            return(1);    
        else if (!q && p[i] == '>' && p[i + 1] != '>' && check_next(p,i,0))
            return(1);
        else if (!q && p[i] == '<' && p[i + 1] != '<' && check_next(p,i,0))
            return(1);    
        i++;
    }
    return(0);
}