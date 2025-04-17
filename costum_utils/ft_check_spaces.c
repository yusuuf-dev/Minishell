#include "../minishell.h"

int		ft_check_spaces(char *s)
{
	size_t	i = 0;
	while (s[i])
	{
		if ((s[i] <= 13 && s[i] >= 11) || s[i] == 9)
			i++;
		else
			return (0);
	}
	return (1);
}