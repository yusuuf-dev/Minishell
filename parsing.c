#include "minishell.h"

int	execute_command(char *path, char **rdl_args, char **envp);
static int	ft_built_in_cmd(char **rdl_args, char ***envp, char **env_paths, int *status, int *s_exit);

char	*ft_getenv(char *s, char **envp)
{
	size_t	i = 0;
	size_t	size = 0;

	size = ft_strlen(s);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], s, size))
		{
			return (ft_strchr(envp[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}

static char     **ft_execute_cmd(char *path, char **av, char **envp)
{
    int     pid;

    pid = fork();
    if (pid == 0)
        execve(path,av,envp);
    else if (pid > 0)
        waitpid(pid,NULL,0);
    return (envp);
}

static  int is_execute_file(char **rdl_args, char **env)
{
    if (!(rdl_args[0][0] == '.' || ft_strchr(rdl_args[0], '/')))
        return (0);
    if (access(rdl_args[0],F_OK) == -1)
    {
        perror("minishell");
        return(1);
    }
    if (access(rdl_args[0],X_OK) == 0)
        ft_execute_cmd(rdl_args[0],rdl_args,env);
    else
        perror("minishell");
    return(1);
}
static void     convert_rdl_vars(char **env, char  **rdl_args)
{
    int i;
	char	*temp;
    i = 1;
    while(rdl_args[i])
    {
		temp = rdl_args[i];
        if (ft_strcmp(rdl_args[i],"~")) // UPDATE ME "ls ~asoufian"
		{
            rdl_args[i] = ft_strdup(ft_getenv("HOME", env));
			free(temp);
		}
        else if(rdl_args[i][0] == '$' && rdl_args[i][1] && rdl_args[i][1] != '$')
		{
            rdl_args[i] = ft_strdup(ft_getenv(&rdl_args[i][1], env));
			free(temp);
		}
        i++;
    }
}
static void free_move(char **rdl_args, size_t i)
{
	size_t	t;
	
	free(rdl_args[i]);
	t = i;
	while (rdl_args[t + 1])
	{
	//	if (t > 0)
	//	{
			rdl_args[t] = rdl_args[t + 1];
	//	}
		t++;
	}
	rdl_args[t] = rdl_args[t + 1];
}
int parse_redirection(char **rdl_args, int *status)
{
	size_t	i = 0;
	char	*fd_temp;
	char	*temp;
	int		append = 0;
	int		fd = 1;
	int		fd_file = 0;

	while (rdl_args[i])
	{
		if (ft_strchr(rdl_args[i], '>'))
		{
			fd_temp = ft_strldup(rdl_args[i], ft_strchr(rdl_args[i], '>') - rdl_args[i]); // parsing the part before '<' if there's any
			if (fd_temp && fd_temp[0])
				fd = costum_atoi(fd_temp, status);
			temp = ft_strchr(rdl_args[i], '>') + 1;
			if (temp && temp[0] == '>')
			{
				append = 1;
				temp++;
			}
		//	if (fd > 1023 || *status == 1) // if the passed 'fd' in the argument is greater than 1023 we need to stop the executing and return an error
		//		return (ft_putstr("minishell: ", 2), ft_putstr(temp, 2), ft_putstr(": Bad file descriptor\n", 2), free(temp), *status = 1, 1); // maybe not needed ?
		//	if (*status == 2) // this is in case the argument is greater than INT_MAX or It doesn't contain an int	
		//		rdl_args[i] = fd_temp; // we need to passe the chars before '>' as an argument, placed before the current one.
		//	else
		//	{
				if (!temp[0])
				{
					free_move(rdl_args, i);
					temp = rdl_args[i];
					if (!temp)
						return(ft_putstr("minishell: syntax error near unexpected token `newline'", 2), free(fd_temp), 1);
				}
				if (append)
					fd_file = open(temp, O_RDWR|O_CREAT|O_APPEND, 00644);
				else
					fd_file = open(temp, O_RDWR|O_CREAT|O_TRUNC, 00644);
				if (fd_file < 0)
					return (perror("minishell: "), free(fd_temp), *status = 1, 1);
				fd = dup2(fd_file, fd);
				if (fd < 0)
					return(ft_putstr("minishell: ", 2), ft_putstr(fd_temp, 2), ft_putstr(": ", 2), perror(""), close(fd_file), free(fd_temp), *status = 1, 1);
				free_move(rdl_args, i);
				if (*status != 2)
					free(fd_temp);
				else
					rdl_args[i] = fd_temp;
		//	}
			i = 0;
		}
		i++;
	}
	if (*rdl_args == NULL)
		return (1);
	return (0);
}

char	**parsing(char *p, char **envp, int *s_exit)
{
    char	*env;
    char	**env_paths = NULL;
    char	**rdl_args;
    char	*path;
    int		i = 0;
    int		status = 0;

	env = ft_getenv("PATH", envp);
	if (env)
    	env_paths = ft_split(env,':');
 	rdl_args = ft_split(ft_isspace_to_space(p),' ');
	if (parse_redirection(rdl_args, &status))
		return (free_all(rdl_args), free_all(env_paths), envp);
	//write(60, "testing", ft_strlen("testing"));
	convert_rdl_vars(envp,rdl_args);
	if (is_execute_file(rdl_args,envp))
		return (free_all(rdl_args), free_all(env_paths), envp);
	if (ft_built_in_cmd(rdl_args, &envp, env_paths, &status, s_exit))
		(void)p;
	else
	{
		while (env && env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(env_paths[i], "/"),rdl_args[0]);
			if (!access(path, F_OK) && !access(path, X_OK))
				return (status = execute_command(path, rdl_args, envp), free(path), free_all(rdl_args), free_all(env_paths), envp);
			free(path);
			i++;
		}
		ft_putstr("minishell: command not found: ", 2);
		ft_putstr(rdl_args[0], 2);
		ft_putstr("\n", 2);
	}
	return (free_all(rdl_args), free_all(env_paths), envp);
}


static int	ft_built_in_cmd(char **rdl_args, char ***envp, char **env_paths, int *status, int *s_exit)
{
	char  **cmds = NULL;
	int   i;

	cmds = ft_split("pwd,cd,export,echo,env,unset,exit", ',');
  i = 0;
	while (i < 10 && cmds[i])
	{
        if (ft_strcmp(cmds[i],rdl_args[0]))
        {
			    i += 9;
          //  ft_excmd_built(rdl_args, i, envp, env_paths);
          //  return(1);
        }
        i++;
	}
	if (i == 10)
		*status = ft_pwd(0, rdl_args, *envp);
	else if (i == 11)
		*status = ft_cd(0, rdl_args, envp);
	else if (i == 12)
		*envp = ft_export(0, rdl_args, *envp, status);
	else if (i == 13)
		*status = ft_echo(0, rdl_args, *envp);
	else if (i == 14)
		*status = ft_env(0, rdl_args, *envp, env_paths);
	else if (i == 15)
		*envp = ft_unset(0, rdl_args, *envp, status);
	else if (i == 16)
	{
		*status = ft_exit(0, rdl_args, *	envp);
		if (*status)
			*s_exit = *status;
		//if (*status == 2)
		//	*s_exit = 0;
		else
			*s_exit = 1;
	}
  free_all(cmds);
	if (i > 9)
		return (1);
	else
		return (0);
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
			perror("execve");
			exit (errno);
		}
		exit (0);
	}
	else
	{
		if (child_pid < 0)
		{
			perror("fork");
			exit (errno);
		}
		wait(&child_info);
	}
	if (WIFEXITED(child_info))
		return (WEXITSTATUS(child_info));
	return (-1);
}
