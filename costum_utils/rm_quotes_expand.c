#include "../minishell.h"

static int	validchar(int c)
{
	if (c == '_')
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

static char *c_strjoinf(char *s1, char c)
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

char *rm_quotes_expand(char *str, char **envp)
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
			q = str[i++];
		else if (q && str[i] == q)
		{
			q = 0;
			i++;
		}
		else if (str[i] == '$' && q != '\'' && validchar(str[i + 1]))
		{
			i++;
			len = 0;
			while (str[i + len] && str[i + len] != ' ' && str[i + len] != '\"' && str[i + len] != '\'' && str[i + len] != '$')
				len++;
			key = ft_strldup(&str[i],len);
			var = ft_getenv(key,envp);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			free(key);
			i += len;
		}
		else
		{
			ptr = c_strjoinf(ptr,str[i]);
			i++;
		}
	}
	free(str);
	return(ptr);
}