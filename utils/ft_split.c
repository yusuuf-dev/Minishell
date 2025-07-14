#include "../minishell.h"

static int	ft_count_wd(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
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
	str = ft_malloc((ed - st + 1) * sizeof(char));
	while (st < ed)
	{
		str[i++] = s[st++];
	}
	str[i] = '\0';
	return (str);
}


char	**ft_split(char *str, char c)
{
	char	**ptr;
	int	i;
	int	j;
	int	st;
	int	wd;

	wd = ft_count_wd(str,c);
	ptr = ft_malloc((wd + 1) * sizeof(char*));
	i = 0;
	j = 0;
	while (str[i] && j < wd)
	{
		while (str[i] == c)
			i++;
		st = i;
		while (str[i] != c && str[i])
			i++;
		ptr[j] = ft_substr(str,st,i);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}