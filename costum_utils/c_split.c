#include "../minishell.h"

static int	ft_count_wd(char *s, char c)
{
	int	i;
	int	count;
    char q;

	i = 0;
	count = 0;
	q = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			q = s[i++];
			if (s[i] != q)
				count++;
			while (s[i] != q)
				i++;
			q = 0;
		}
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_substr(char *s, int st, int ed)
{
	char	*str;
	int	i;

	i = 0;
	str = malloc((ed - st + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (st < ed)
	{
		str[i++] = s[st++];
	}
	str[i] = '\0';
	return (str);
}

char	**split_q(char *str, char c, char **envp, unsigned char *status)
{
	char	**ptr;
	size_t	i;
	size_t	j;
	size_t	st;
	size_t	wd;
	char q = 0;


	wd = (size_t)ft_count_wd(str,c);
	ptr = malloc((wd + 1) * sizeof(char*));
	if(!ptr)
		return(NULL);
	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] == c)
			i++;
		st = i;
		while (str[i] != c && str[i])
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				q = str[i];
				i++;
				while (str[i] != q)
					i++;
			}
			i++;
		}
		ptr[j] = ft_substr(str,st,i);
		if (!ptr[j])
			return(free_all(ptr));
		if (c != '|')
			ptr[j] = rm_quotes_expand(ptr[j],envp,status);
		j++;
		q = 0;
	}
	ptr[j] = NULL;
	return (ptr);
}


int  found_q(char *s) 
{
    size_t  i;
	int		f_s;
	int		f_d;
	int		found;

    i = 0;
	f_s = 0;
	f_d = 0;
	found = 0;
    while (s[i])
    {
		if (s[i] == '\'' && !f_d)
			f_s = !f_s;
		if (s[i] == '\"' && !f_s)
			f_d = !f_d;
		if (s[i] == '\"' || s[i] == '\'')
			found++;
        i++;
    }
    if((f_d || f_s) && found > 0)
        return(-1);
	else if(found == 0)
		return(0);
    return(1);
}



char	**c_split(char *str, char c, char **envp, unsigned char *func_status)
{
    char    **ptr;
	int		status;
	int		i;

	i = 0;
	status = found_q(str);
	if (status == -1)
		return (NULL);
	else if (status == 1)
		ptr = split_q(str,c,envp, func_status);
    else
	{
        ptr = ft_split(str,c);
		while (ptr[i])
		{
			ptr[i] = rm_quotes_expand(ptr[i],envp, func_status);
			i++;
		}
	}
    return(ptr);
}