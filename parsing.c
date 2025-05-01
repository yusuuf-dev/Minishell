#include "minishell.h"

int	execute_command(char *path, char **rdl_args, char **envp, int fd);
static int	ft_built_in_cmd(char **rdl_args, char ***envp, char **env_paths, int *status, int *s_exit);

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

char	*ft_getenv(char *s, char **envp)
{
	size_t	i = 0;
	size_t	size = 0;

	if (!s || !(s[0]))
		return (NULL);
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

char	**parsing(char **p, char **envp, int *s_exit)
{
    char	*env;
    char	**env_paths = NULL;
    char	**rdl_args;
    char	*path;
    int		i = 0;
    int		status = 0;
	char	*delimiter = NULL;
	char	*tmp;
	int 	fd_tmp = 0;

    if (found_q(*p) == -1)
        {return (ft_putstr("Error unclosed quotes\n", 2), envp);}
	env = ft_getenv("PATH", envp);
	if (env)
    	env_paths = ft_split(env,':');
	while (found_heredoc(*p))
	{
		delimiter = heredoc_delimiter(*p);
		if (!delimiter)
			return(envp); // failed malloc protection
		fd_tmp = open("/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC , 0777);
		if (fd_tmp < 0)
			return (perror(""), envp);
		while (1)
		{
			tmp = readline("> ");
			if (!tmp)
				break;
			if (ft_strcmp(tmp,delimiter))
			{
				free(tmp);
				break;
			}
			c_putstr_fd(fd_tmp,tmp);
			free(tmp);
		}
		free(delimiter);
		close(fd_tmp);
		fd_tmp = open("/tmp/tmp.txt", O_RDWR, 0777);
		if (fd_tmp < 0)
			return (perror(""), envp);
	}
    *p = convert_env_var(*p,envp);
    rdl_args = c_split(*p,' ');
	if (is_execute_file(rdl_args,envp))
		return (free_all(rdl_args), free_all(env_paths), envp);
	if (ft_built_in_cmd(rdl_args, &envp, env_paths, &status, s_exit))
		(void)*p;
	else
	{
		while (env && env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(env_paths[i], "/"),rdl_args[0]);
			if (!access(path, F_OK) && !access(path, X_OK))
				return (status = execute_command(path, rdl_args, envp, fd_tmp), free(path), free_all(rdl_args), free_all(env_paths), envp);
			free(path);
			i++;
		}
		ft_putstr("minishell: command not found: ", 2);
		ft_putstr(rdl_args[0], 2);
		ft_putstr("\n", 2);
	}
	close(fd_tmp);
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

int	execute_command(char *path, char **rdl_args, char **envp , int fd)
{
	int	child_pid = 0;
	int	child_info = 0;
//	char *read_buf = ft_calloc(sizeof(char) * 10);

	if (dup2(fd, 0) < 0)
		return (perror(""), errno);
	//if (lseek(fd, 0, SEEK_SET) < 0 )
	//	return (perror (""), errno);
	/*if (read(fd, read_buf, 5) < 0)
		return (perror(""), errno);
	read_buf[5] = 0;*/

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
