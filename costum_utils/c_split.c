#include "../minishell.h"

char *rm_quotes(char *str)
{
	size_t	i;
	size_t	j;
	char	*ptr;
	char	q;

	i = 0;
	j = 0;
	q = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '\"'))
			q = str[i];
		else if (str[i] != q)
			j++;
		else
			q = 0;
		i++;
	}
	ptr = malloc((j + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '\"'))
			q = str[i];
		else if(str[i] != q)
		{
			ptr[j] = str[i];
			j++;
		}
		else
			q = 0;
		i++;
	}
	ptr[j] = '\0';
	return(ptr);
}

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

char	**split_q(char *str, char c)
{
	char	**ptr;
	int	i;
	int	j;
	int	st;
	int	wd;
	char q;
	char	*tmp;


	wd = ft_count_wd(str,c);
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
		tmp = ptr[j];
		ptr[j] = rm_quotes(ptr[j]);
		free(tmp);
		if (!ptr[j++])
			return(free_all(ptr));
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


char	**c_split(char *str, char c)
{
    char    **ptr;
	int		status;

	status = found_q(str);
	if (status == -1)
		return (NULL);
	else if (status == 1)
		ptr = split_q(str,c);
    else
        ptr = ft_split(str,c);
    return(ptr);
}