#include "../minishell.h"

void ft_strcpy(char *dest, char *src)
{
	size_t	i = 0;

	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}
