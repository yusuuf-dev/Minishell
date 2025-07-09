#include "../minishell.h"

static char *charjoinf(char *s1, char c)
{
	size_t i;
	size_t len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = malloc((len + 2) * sizeof(char));
	if (!ptr)
		return(NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	ptr[i] = 0;
	free(s1);
	return (ptr);
}

char    *rm_quotes_expand(char *str, char **envp, unsigned char *status)
{
	size_t	i = 0;
	size_t	len = 0;
	char	q = 0;
	char	*ptr = NULL;
	char	*key = NULL;
	char	*var = NULL;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '\"'))
			q = str[i];
		else if (q && str[i] == q)
			q = 0;
		else if (str[i] == '$' && q != '\'' && str[i + 1] == '?')
		{
			var = ft_getenv("?", envp, status);
			ptr = ft_strjoinf(ptr,var);
			i++;
		}
		else if (str[i] == '$' && q != '\'' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			len = 0;
			while (str[i + len] && ft_isalnum(str[i + len]))
				len++;
			key = ft_strldup(&str[i],len);
			var = ft_getenv(key,envp,status);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			free(key);
			i += len - 1;
		}
		else
			ptr = charjoinf(ptr,str[i]);
		i++;
	}
	//free(str);
	return(ptr);
}

char    *expand(char *str, char **envp, unsigned char *status)
{
	size_t	i = 0;
	size_t	len = 0;
	char	q = 0;
	char	*ptr = NULL;
	char	*key = NULL;
	char	*var = NULL;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (!q && (str[i] == '\'' || str[i] == '\"'))
		{
			q = str[i];
			ptr = charjoinf(ptr,str[i]);
		}
		else if (q && str[i] == q)
		{
			q = 0;
			ptr = charjoinf(ptr,str[i]);
		}
		else if (str[i] == '$' && q != '\'' && str[i + 1] == '?')
		{
			var = ft_getenv("?", envp, status);
			ptr = ft_strjoinf(ptr,var);
			i++;
		}
		else if (str[i] == '$' && q != '\'' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			len = 0;
			while (str[i + len] && ft_isalnum(str[i + len]))
				len++;
			key = ft_strldup(&str[i],len);
			var = ft_getenv(key,envp,status);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			free(key);
			i += len - 1;
		}
		else
			ptr = charjoinf(ptr,str[i]);
		i++;
	}
	//free(str);
	return(ptr);
}

