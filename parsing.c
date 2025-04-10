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
    rdl_args = ft_split(ft_remove_isspace(temp),' ');
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
	// free rdl_args;
	return (envp);
}
