#include "../minishell.h"

static size_t	ft_count_wd(char *s, char c)
{
	size_t	i;
	size_t	count;
    char 	q;

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


static size_t	skip_quotes(char *str, char c, size_t i)
{
	char	q;

	q = 0;
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
	return (i);	
}

static char		**core_function(char *str, char c, size_t i, size_t j)
{
	char	**ptr;
	size_t	st;
	size_t	wd;

	wd = ft_count_wd(str,c);
	ptr = malloc((wd + 1) * sizeof(char*));
	if(!ptr)
		return(NULL);
	while (str[i] && j < wd)
	{
		while (str[i] == c)
			i++;
		st = i;
		i = skip_quotes(str,c,i);
		ptr[j] = ft_substr(str,st,i);
		if (!ptr[j])
			return(free_all(ptr));
		if(ptr[j])
			j++;				
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**c_split(char *str, char c, char **envp, unsigned char *func_status)
{
	char	**ptr;
	// size_t	i;

	// ptr = core_function(str,c,0,0);
	// if (!ptr)
	// 	return (NULL);
	// if ( c != '|')
	// {
	// 	i = 0;
	// 	while (ptr[i])
	// 	{
	// 		ptr[i] = rm_quotes_expand(ptr[i],envp,func_status);
	// 		i++;
 	// 	}
	// }
	str = rm_quotes_expand(str,envp,func_status);
	if (!str)
		return (NULL);
	ptr = core_function(str,c,0,0);
	if (!ptr)
		return (NULL);
	return (ptr);
}


// char	**c_split(char *str, char c, char **envp, unsigned char *func_status)
// {
// 	char	**ptr;
// 	size_t	i;
// 	size_t	j;
// 	size_t	st;
// 	size_t	wd;
// 	char q = 0;


// 	wd = (size_t)ft_count_wd(str,c);
// 	ptr = malloc((wd + 1) * sizeof(char*));
// 	if(!ptr)
// 		return(NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i] && j < wd)
// 	{
// 		while (str[i] == c)
// 			i++;
// 		st = i;
// 		while (str[i] != c && str[i])
// 		{
// 			if (str[i] == '\"' || str[i] == '\'')
// 			{
// 				q = str[i];
// 				i++;
// 				while (str[i] != q)
// 					i++;
// 			}
// 			i++;
// 		}
// 		ptr[j] = ft_substr(str,st,i);
// 		if (!ptr[j])
// 			return(free_all(ptr));
// 		if (c != '|')
// 			ptr[j] = rm_quotes_expand(ptr[j],envp,func_status);
// 		if(ptr[j])
// 			j++;
// 		q = 0;
// 	}
// 	ptr[j] = NULL;
// 	return (ptr);
// }


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
