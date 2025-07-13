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

// char *rm_quotes_02(char *str)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*ptr;
// 	char	q;

// 	i = 0;
// 	j = 0;
// 	q = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (i = )
// 	}
	
// }