#include "../minishell.h"

char	**ft_duplicate(char	**s, size_t add_size)
{
	size_t	i;
	size_t	size;
	char	**p;

	i = size = 0;
	while (s[size])
		size++;
	p = ft_calloc(sizeof(char *) * (size + 1 + add_size));
	if (!p)
		exit (-1);
	while (s[i])
	{
		p[i] = ft_strdup(s[i]);
		i++;
	}	
	return (p);
}