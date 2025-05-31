#include "../minishell.h"
char	*ft_substr_c(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s || (len - start) == 0)
		return (NULL);
	i = 0;
	p = malloc(len - start + 1);
	while ((start + i) < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}