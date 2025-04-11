#include "minishell.h"

// char *built_cmd(char *cmd)
// {
//     return(NULL);
//     return ("echo");
// }

int	execute_command(char *path, char **rdl_args, char **envp);

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

char	**parsing(char *p, char **envp, int *s_exit)
{
    char	*env;
    char	**env_paths;
    char	**rdl_args;
    char	*path;
    char	*temp;
    int		i = 0;
    int		status = 0;

    	env= getenv("PATH");
  	if (!env)
   	{	
		printf("home PATH not found\n");
       		return (envp);
   	}
    	env_paths = ft_split(env,':');
    	temp = ft_strdup(p);
    	ft_isspace_to_space(temp); // replaces all isspace with a space
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
	else if (!ft_strcmp("exit", rdl_args[0], 4) && !rdl_args[0][5])
	{
		status = ft_exit(0, rdl_args, envp);
		if (status)
			*s_exit = status;
		if (status == 2)
			*s_exit = 0;
		else
			*s_exit = 1;
	}
	else
	{
		while (env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(env_paths[i], "/"),rdl_args[0]);
			if (!access(path, F_OK) && !access(path, X_OK))
			{
				status = execute_command(path, rdl_args, envp);
				return (free(path), free_all(rdl_args), free_all(env_paths), envp);
			}
//				execve(path,rdl_args,envp)
			free(path);
			i++;
		}
	}
	free_all(rdl_args);
	free_all(env_paths);
	return (envp);
}

int	execute_command(char *path, char **rdl_args, char **envp)
{
	int	child_pid = 0;
	int	child_info = 0;

	child_pid = fork();
	if (!child_pid)
	{
		if (execve(path, rdl_args, envp))
		{
			printf("Error while executing a command\n");
			exit (-99);
		}
		exit (0);
	}
	else
	{
		if (child_pid < 0)
		{
			printf("Error while creating a child\n");
			exit (-1);
		}
		wait(&child_info);
	}
	if (WIFEXITED(child_info))
		return (WEXITSTATUS(child_info));
	return (-1);
}
