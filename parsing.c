#include "minishell.h"

// char *built_cmd(char *cmd)
// {
//     return(NULL);
//     return ("echo");
// }

void	ft_print_env(char **p)
{
	size_t	i = 0;
	while (p[i])
	{
		printf("%s\n", p[i]);
		i++;
	}
}

char	**ft_duplicate(char	**s)
{
	size_t	i;
	size_t	size;
	char	**p;

	i = size = 0;
	while (s[size])
		size++;
	p = malloc(sizeof(char *) * (size + 1));
	if (!p)
		exit (-1);
	while (s[i])
	{
		p[i] = ft_strdup(s[i]);
		i++;
	}
	p[i] = 0;
	return (p);
}

char	**parsing(char *p, char **envp)
{
    char    *env;
    char    **env_paths;
    char    **rdl_args;
    char   *path;
    char	*temp;
    int i = 0;
    int	status = 0;

    env = getenv("PATH");
    if (!env)
    {
        printf("home PATH not found\n");
        return (envp);
    }
    env_paths = ft_split(env,':');
    temp = ft_strdup(p);
    temp = ft_remove_isspace(temp);
    rdl_args = ft_split(temp,' ');
    free(temp);
	if (!ft_strcmp("echo", rdl_args[0], 4) && !rdl_args[0][4])
		status = ft_echo(0, rdl_args, envp);
	else if (!ft_strcmp("pwd", rdl_args[0], 3) && !rdl_args[0][3])
		status = ft_pwd(0, rdl_args, envp);
	else if (!ft_strcmp("cd", rdl_args[0], 2) && !rdl_args[0][2])
		status = ft_cd(0, rdl_args, envp);
	else if (!ft_strcmp("export", rdl_args[0], 6) && !rdl_args[0][6])
	{
		ft_print_env(envp);
		envp = ft_export(0, rdl_args, envp, &status);
		ft_print_env(envp);
	}
	else if (!ft_strcmp("unset", rdl_args[0], 5) && !rdl_args[0][5])
	{
		ft_print_env(envp);
		envp = ft_unset(0, rdl_args, envp, &status);
		ft_print_env(envp);
	}
	else if (!ft_strcmp("env", rdl_args[0], 3) && !rdl_args[0][4])
	{
		status = ft_env(0, rdl_args, envp, env_paths);

	}
	else
	{
		while (env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(env_paths[i], "/"),rdl_args[0]);
			if(execve(path,rdl_args,NULL) !=  -1)
				break;
			free(path);
			i++;
		}
	}
	free_all(rdl_args);
	free_all(env_paths);
	return (envp);
}
