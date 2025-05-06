#include "../minishell.h"

static void c_putstr_fd(int fd, char *s)
{
	size_t i = 0;

	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

static int	validchar(int c)
{
	if (c == '_')
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else
		return (0);
}

static char *c_strjoinf(char *s1, char c)
{
	size_t i;
	size_t len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = malloc((len + 2) * sizeof(char));
	if (!ptr)
		return(NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	ptr[i] = 0;
	free(s1);
	return (ptr);
}

static char *c_expand(char *str, char **envp)
{
	size_t	i = 0;
	size_t	len = 0;
	char	*ptr = NULL;
	char	*key = NULL;
	char	*var = NULL;

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && validchar(str[i + 1]))
		{
			i++;
			len = 0;
			while (str[i + len] && str[i + len] != ' ' && str[i + len] != '\"' && str[i + len] != '\'' && str[i + len] != '$')
				len++;
			key = ft_strldup(&str[i],len);
			var = ft_getenv(key,envp);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			free(key);
			i += len;
		}
		else
		{
			ptr = c_strjoinf(ptr,str[i]);
			i++;
		}
	}
	free(str);
	return(ptr);
}

int     ft_isheredoc(char **p, char **envp)
{
    char    *tmp;
    char    *dl;
	int		fd;
	int		isquote = 0;

    (void)envp;//need use later when expend on input lines

	if (found_heredoc(*p) == -1)
		return (0);
    while (found_heredoc(*p))
	{
		dl = heredoc_delimiter(*p,&isquote);
		if (!dl)
			return(-1); // failed malloc protection
		fd = open("/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC , 0777);
		if (fd < 0)
			return (perror(""),0);
		while (1)
		{
			tmp = readline("> ");
			if (!tmp)
				break;
			if (ft_strcmp(tmp,dl))
			{
				free(tmp);
				break;
			}
			if (!isquote)
				tmp = c_expand(tmp,envp);
			c_putstr_fd(fd,tmp);
			free(tmp);
		}
		free(dl);
		close(fd);
		fd = open("/tmp/tmp.txt", O_RDWR, 0777);
		if (fd < 0)
			return (perror(""), 0);
		if (dup2(fd, 0) < 0)
			return (perror(""), errno);
	}
    return(1);
}