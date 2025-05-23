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

static char *c_strjoinf(char *s1, char c)
{
	size_t i;
	size_t len;
	char	*ptr;

	len = ft_strlen(s1);
	ptr = ft_malloc((len + 2) * sizeof(char));
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i++] = c;
	ptr[i] = 0;
	return (ptr);
}

static char *c_expand(char *str, char **envp, unsigned char *status)
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
		if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1])))
		{
			i++;
			len = 0;
			while (str[i + len] && ft_isalnum(str[i + 1]))
				len++;
			key = ft_strldup(&str[i], len);
			var = ft_getenv(key, envp, status);
			if (var)
				ptr = ft_strjoinf(ptr,var);
			i += len;
		}
		else
		{
			ptr = c_strjoinf(ptr,str[i]);
			i++;
		}
	}
	return(ptr);
}

int     ft_isheredoc(char *p, char **envp, unsigned char *status)
{
    char    *tmp;
    char    *dl;
	int		fd;
	int		isquote = 0;


  //  while (found_heredoc(*p))
//{
	if (!(p[2]) && ( p[2] == '<' || p[2] == '>'))
		{return(ft_putstr("minishell: syntax error near unexpected token `newline'\n", 2), -1);}
		dl = heredoc_delimiter(p,&isquote);
		fd = open("/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC , 0777);
		if (fd < 0)
			return (perror(""), 0);
		while (1)
		{
			tmp = readline("> ");
			//if (!tmp)
		//		break;
			if (!tmp || ft_strcmp(tmp,dl))
			{
				break;
			}
			if (!isquote && tmp[0])
				tmp = c_expand(tmp, envp, status);
			c_putstr_fd(fd,tmp);
		}
		free(dl);
		close(fd);
		fd = open("/tmp/tmp.txt", O_RDWR, 0777);
		if (fd < 0)
			return (perror(""), errno);
		if (dup2(fd, 0) < 0)
			return (close(fd), perror(""), errno);
		close(fd);
		return(0);
}
