#include "../minishell.h"

int     ft_pwd(char **argv, char **envp, t_data *data)
{
    char    *p;

	(void)argv;
	(void)envp;
    p = NULL;

	if (!data->cwd)
	{
		p = getcwd(p, 0);
		if (!p)
		{
			return (perror("pwd: getcwd: "), 1);
		}
		data->cwd = ft_strdup_env(p);
		free(p);
	}
	ft_putstr(data->cwd, 1);
	write(1, "\n", 1);
    return (0);
}
