#include "../minishell.h"

char	**ft_duplicate(char	**s)
{
	size_t	i;
	size_t	size;
	char	**p;

	i = size = 0;
	while (s[size])
		size++;
	p = malloc(sizeof(char *) * (size + 1));
	if (!p)
		exit (-1);
	while (s[i])
	{
		p[i] = ft_strdup(s[i]);
		i++;
	}
	p[i] = 0;
	return (p);
}