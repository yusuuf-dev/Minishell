#include "../minishell.h"

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	s = ft_calloc(18);
	i = 15;
	if (!n)
		return (s[0] = '0', s);
	while (n)
	{
		s[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	ft_strcpy(s, (s + i + 1));
	return (s);
}
