#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	t;
	char	*p;

	i = 0;
	t = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while(s2[t])
	{
		p[t + i] = s2[t];
		t++;
	}
	p[t + i] = 0;
	return (p);
}

size_t  ft_strlen(char *s)
{
        size_t  i;

        if (!s)
                return (0);
        i = 0;
        while (s[i])
                i++;
        return (i);
}
int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t  i;

        i = 0;
        if (!s1 || !s2)
                exit(-1);
        while(s1[i] && i < n)
        {
                if (s1[i] - s2[i])
                        return (s1[i] - s2[i]);
                i++;
        }
        i--;
        return (s1[i] - s2[i]);
}

int     ft_strcmp(char *s1, char *s2)
{
    int     i;

    i = 0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return(0);
        i++;
    }
    return(1);
}

char    *ft_strchr(char *s, char c)
{
        size_t  i;

        i = 0;
        if (!s)
                return (NULL);
        while (s[i])
        {
                if (s[i] == c)
                        return (s + i);
                i++;
        }
        return (NULL);
}

