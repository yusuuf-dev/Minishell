#include "../minishell.h"

static int	ft_isalpha(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

static int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else
		return (0);
}

static  char    *c_strpbrk(char *s)
{
    size_t  i;

    i =  0;
    while(s[i])
    {
        if (!ft_isalnum(s[i]) && s[i] != '_') 
            return (&s[i]);
        i++;
    }
    return (&s[i]);
}


char    *convert_env_var(char *s,char **envp)
{
    size_t  i = 0;
    int     f_d = 0;
    int     f_s = 0;
    char    *extract = NULL;
    char    *var = NULL;
    char    *left_side = NULL;
    char    *right_side = NULL;

    while (s[i])
    {        
        if (s[i] == '\'' && !f_d)
			f_s = !f_s;
        if (s[i] == '\"' && !f_s)
            f_d = !f_d;
        if (s[i] == '$' && !f_s && (ft_isalpha(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
        {
            extract = ft_strldup(&s[i + 1], c_strpbrk(&s[i + 1]) - &s[i + 1]);
            var = ft_getenv(extract, envp);
            left_side = ft_strldup(s, i);
            if (var)
                left_side = ft_strjoinf(left_side, var);
            right_side = ft_strdup(c_strpbrk(&s[i + 1]));
            free(s);
            s = ft_strjoinf(left_side, right_side);
            free(right_side);
            free(extract);
            i += ft_strlen(var);
        }
        if (s[i])
            i++;
    }
    return (s);
}
