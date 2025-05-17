#include "minishell.h"

// char	*ft_getenv(char *s, char **envp)
// {
// 	size_t	i = 0;
// 	size_t	len = 0;

// 	if (!s || !(s[0]))
// 		return (NULL);
// 	len = ft_strlen(s);
// 	while (envp[i])
// 	{
// 		if (!ft_strncmp(envp[i], s, len) && envp[i][len] == '=')
// 			return (ft_strchr(envp[i], '=') + 1);
// 		i++;
// 	}
// 	return (NULL);
// }

int	execute_command(char *path, char **rdl_args, char **envp);
static int	ft_built_in_cmd(char **rdl_args, char ***envp, char **env_paths, unsigned char *status, int *s_exit);

static int     c_strncmp(const char *s1, const char *s2) // there's another copy of this in ft_export
{
    size_t  i;

    i = 0;
    while(s1[i] && s1[i] != '=')
    {
        if (s1[i] - s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
	if (!(s2[i]))
		return (0);
    return (s1[i] - s2[i]);
}

static void ft_strcpy(char *dest, char *src)
{
	size_t	i = 0;

	while(src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}

static char	*ft_itoa(int n)
{
	char	*s = ft_calloc(17);
	int		i = 15;

	if (!n)
		return (s[0] = '0', s);
	while (n)
	{
		s[i] = (n % 10) + '0';
		i--;
		n = n / 10;
	}
	ft_strcpy(s, (s + i + 1));
	return (s);
}
char	*ft_getenv(char *s, char **envp, unsigned char *status)
{
	size_t	i = 0;
	size_t	size = 0;

	size = ft_strlen(s);
	while (envp[i])
	{
		if (!c_strncmp(envp[i], s))
		{
			return (ft_strchr(envp[i], '=') + 1);
		}
		if (s[0] == '?' && !s[1])
			return (i = *status, ft_itoa(i));
		i++;
	}
	return (NULL);
}

static char     **ft_execute_cmd(char *path, char **av, char **envp)
{ // I need to add the status here too, so I can get the status of I run a local program (not in the PATH)
    int     pid;

	__sighandler_t old_handler = signal(SIGINT, SIG_IGN);
	if (old_handler == SIG_ERR)
	{
		perror("signal ");
		exit (-1);
	}
    pid = fork();
	if (pid == -1)
	{
		perror("");
		exit (-1);
	}
    if (pid == 0)
        execve(path,av,envp);
    else if (pid > 0)
	{
        waitpid(pid,NULL,0);
		signal(SIGINT, old_handler);
	}
    return (envp);
}

static  int is_execute_file(char **rdl_args, char **env, unsigned char *status)
{
	int is_a_file = 0;

	if (!rdl_args[0])
		return (1);
    if (!(rdl_args[0][0] == '.' || (ft_strchr(rdl_args[0], '/'))))// && rdl_args[0][ft_strlen(rdl_args[0] - 1)] != '/')))
    {    return (0);}
	is_a_file = open(rdl_args[0], O_DIRECTORY); // check for errno in case open fails for some reason, and return error ?
	if (is_a_file != -1)
		{return (*status = 126, close(is_a_file), ft_putstr("minishell: ", 2), ft_putstr(rdl_args[0], 2), ft_putstr(": Is a directory\n", 2), 1);} // need to set the status to 126;
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

static void			ft_space(char *s)
{
	size_t	i = 0;
	int		f_s = 0;
	int		f_d = 0;

	while(s[i])
	{
		if(s[i] == '\'' && !f_d)
			f_s = !f_s;
		if(s[i] == '\"' && !f_s)
			f_d = !f_d;
		if(!f_d && !f_s && s[i] >= 9 && s[i] <= 13)
			s[i] = ' ';
		i++;
	}
}

char	**parsing(char **p, char **envp, int *s_exit, unsigned char *status)
{
    char	*env;
    char	**env_paths = NULL;
    char	**rdl_args;
    char	*path;
    int		i = 0;

    if (found_q(*p) == -1) // check if the quotes are closed;
        {return (ft_putstr("Error unclosed quotes\n", 2), envp);}
	ft_space(*p); 
	if(parse_redirection(p, status, envp)) // this also removes spaces;
	 	return (envp);
	//*p = convert_env_var(*p, envp);
	env = ft_getenv("PATH", envp, status);
	if (env)
		env_paths = ft_split(env,':');
    rdl_args = c_split(*p,' ', envp, status);
	
	if (is_execute_file(rdl_args, envp, status))
		return (free_all(rdl_args), free_all(env_paths), envp);
	if (ft_built_in_cmd(rdl_args, &envp, env_paths, status, s_exit))
		(void)*p;
	else
	{
		while (env && env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(env_paths[i], "/"),rdl_args[0]);
			if (!access(path, F_OK) && !access(path, X_OK))
				return (*status = execute_command(path, rdl_args, envp), free(path), free_all(rdl_args), free_all(env_paths), envp);
			free(path);
			i++;
		}
		ft_putstr("minishell: command not found: ", 2);
		ft_putstr(rdl_args[0], 2);
		ft_putstr("\n", 2);
		*status = 127;
	}
	return (free_all(rdl_args), free_all(env_paths), envp);
}

static int	ft_built_in_cmd(char **rdl_args, char ***envp, char **env_paths, unsigned char *status, int *s_exit)
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
		*status = ft_pwd(rdl_args, *envp);
	else if (i == 11)
		*status = ft_cd(rdl_args, envp);
	else if (i == 12)
		*envp = ft_export(rdl_args, *envp, status);
	else if (i == 13)
		*status = ft_echo(rdl_args);
	else if (i == 14)
		*status = ft_env(rdl_args, *envp, env_paths);
	else if (i == 15)
		*envp = ft_unset(rdl_args, *envp, status);
	else if (i == 16)
	{
		*status = ft_exit(rdl_args, *envp);
		//if (*status)
		//	*s_exit = *status;
		//if (*status == 2)
		//	*s_exit = 0;
	//	else
		if (*status != 1)
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

	//child_exists = 1;
	__sighandler_t old_handler = signal(SIGINT, SIG_IGN);
	if (old_handler == SIG_ERR)
	{
		perror("signal ");
		exit (-1);
	}
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	if (!child_pid)
	{
		//child_exists = 0;
		if (execve(path, rdl_args, envp))
		{
			perror("execve");
			exit(errno);
		}
		exit(0);
	}
	else
	{
		wait(&child_info); // check for error
		signal(SIGINT, old_handler);
		//child_exists = 0;*/
		//printf("child waiting status in excute_command: %d\n",waitpid(child_pid, &child_info, 0));
	}
	if (WIFEXITED(child_info))
		return (WEXITSTATUS(child_info));
	return (-1);
}