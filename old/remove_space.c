#include "minishell.h"

char	*ft_remove_isspace(char *s)
{
	size_t	i;
	size_t	t;
	size_t	count;
	char	*p;

	i = 0;
	t = 0;
	count = 0;
	while ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
		t++;
	while (s[i + t])
	{
		if ((s[i + t] >= 9 && s[i + t] <= 13) || s[i + t] == ' ')
		{
			while ((s[i + t] >= 9 && s[i + t] <= 13) || s[i + t] == ' ')
				t++;
			if (s[i + t])
			{
				count++;
				i++;
			}
		}
		else
			i++;
	}
	p = malloc(i + count + 2);
	i = t = 0;
	while ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
		t++;
	while (s[t])
	{
	//	p[i] = s[t];
		if ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
		{
			while ((s[t] >= 9 && s[t] <= 13) || s[t] == ' ')
				t++;
			if (s[t])
			{
				p[i] = ' ';
				i++;
			}
		}
		else
		{
			p[i] = s[t];
			t++;
			i++;
		}
//		i++;
	}
	p[i] = 0;
	free(s);
	return (p);
}
