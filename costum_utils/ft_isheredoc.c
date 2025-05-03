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

int     ft_isheredoc(char **p, char **envp)
{
    char    *tmp;
    char    *dl;
	int		fd;

    (void)envp;//need use later when expend on input lines

	if (found_heredoc(*p) == -1)
		return (0);
    while (found_heredoc(*p))
	{
		dl = heredoc_delimiter(*p);
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