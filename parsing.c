#include "minishell.h"

/*// char	*ft_getenv(char *s, char **envp)
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
// }*/

int			execute_command(char *path, t_data *data);
static int	ft_built_in_cmd(t_data *data);

/*static void		ft_space(char *s)
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
}*/

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

static int	ft_execute_cmd(t_data *data)
{ // I need to add the status here too, so I can get the status of I run a local program (not in the PATH)
    int     pid = 0;
	int		child_info = 0;

	if (!(data->is_a_pipe))
    	pid = fork();
	if (pid == -1)
	{
		perror("");
		exit (-1);
	}
    if (pid == 0 || data->is_a_pipe)
	{
		if (sigaction(SIGINT, &(data->OLD_SIG_INT), NULL))
			return (perror(""), errno);
        if (sigaction(SIGQUIT, &(data->OLD_SIG_QUIT), NULL))
			return (perror(""), errno);
		execve(data->rdl_args[0], data->rdl_args, data->envp);
		perror("");
		// free allocated memory
		exit (errno);
	}
    else if (pid > 0)
	{
		if (sigaction(SIGINT, &(data->S_SIG_IGN), NULL))
			return (perror(""), errno);
        waitpid(pid, &child_info, 0);
		if (sigaction(SIGINT, &(data->SIG_INT), NULL) == -1)
			return (perror(""), errno);
		if (WIFEXITED(child_info))
			data->status = WEXITSTATUS(child_info);
		else if (WIFSIGNALED(child_info))
		{
			data->status =  ((child_info & 127) + 128);
			if (!data->is_a_pipe && data->status == 131)
			{
				ft_putstr("Quit (core dumped)\n", 1);
			}
			else if (!data->is_a_pipe && data->status == 130)
			{	
				write(1, "\n", 1);
			}
		}
	}
    return (200);
}

static  int executable(t_data *data)
{
	int is_a_file = 0;

	if (!data->rdl_args[0])
		return (1);
    if (!(ft_strchr(data->rdl_args[0], '/')))
    {    return (0);}
	is_a_file = open(data->rdl_args[0], O_DIRECTORY); // check for errno in case open fails for some reason, and return error ?
	if (is_a_file != -1)
		{return (data->status = 126, close(is_a_file), ft_putstr("minishell: ", 2), ft_putstr(data->rdl_args[0], 2), ft_putstr(": Is a directory\n", 2), 1);} // need to set the status to 126;
    if (access(data->rdl_args[0],F_OK) == -1)
    {
        perror("minishell");
        return(data->status = 127, 127);
    }
    if (access(data->rdl_args[0],X_OK) == 0)
        return (ft_execute_cmd(data));
    else
        perror("minishell");
    return(data->status = 126, 1);
}
char	**parsing(t_data *data)
{
    char	*env;
    char	*path;
	char 	*msg = NULL;
    int		i = 0;
	int		is_a_file = 0;

  //  if (found_q(data->p_rdl) == -1) // check if the quotes are closed;
   //     {return (ft_putstr("Error unclosed quotes\n", 2), data->envp);}
	//ft_space(data->p_rdl);
	//if(parse_redirection(&(data->p_rdl), &(data->status), data->envp, data)) // this also removes spaces;
	if(parse_redirection(&(data->p_rdl), data))
	 	return (data->envp);
	env = ft_getenv("PATH", data->envp, &(data->status));
	if (env)
		data->env_paths = ft_split(env, ':');
	else
		data->env_paths = NULL; // In case we unset the PATH later, the pointer will be pointing to a non-valid memory (dangling pointer)
    data->rdl_args = c_split(data->p_rdl,' ', data->envp, &(data->status));
	
	if (executable(data)) // next 
		return (free_all(data->rdl_args), free_all(data->env_paths), data->envp);
	if (ft_built_in_cmd(data))
		(void)data->p_rdl;
	else
	{	
		while (env && data->env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(data->env_paths[i], "/"),data->rdl_args[0]);
			if (!access(path, F_OK))
			{
				if (!access(path, X_OK))
				{
					is_a_file = open(path, O_DIRECTORY);
					if (is_a_file == -1) // check for errno
					{
						if (execute_command(path, data)) // need to do cleanup since this now returns on error
							return (data->envp);
						return (free(path), free_all(data->rdl_args), free_all(data->env_paths), data->envp);
						//return (data->status = execute_command(path, data), free(path), free_all(data->rdl_args), free_all(data->env_paths), data->envp);
					}
					close(is_a_file);
				}
				else
				{
					if (!msg)
					{
						msg = ft_strjoin("minishell: ", path);
						msg = ft_strjoinf(msg, ": Permission denied");
						msg = ft_strjoinf(msg, "\n");
					}
					data->status = 126;
				}
			}
			free(path);
			i++;
		}
		if (data->status != 126)
		{
			ft_putstr(data->rdl_args[0], 2);
			ft_putstr(": command not found\n", 2);
			data->status = 127;
		}
		else
		{
			ft_putstr(msg, 2);
			free(msg);
		}
	}
	return (free_all(data->rdl_args), free_all(data->env_paths), data->envp);
}

static int	ft_built_in_cmd(t_data *data)
{
	char  **cmds = NULL;
	int   i;

	cmds = ft_split("pwd,cd,export,echo,env,unset,exit", ',');
  	i = 0;
	while (i < 10 && cmds[i])
	{
        if (ft_strcmp(cmds[i],data->rdl_args[0]))
			    i += 9;
        i++;
	}
	if (i == 10)
		data->status = ft_pwd(data->rdl_args, data->envp);
	else if (i == 11)
		data->status = ft_cd(data->rdl_args, &(data->envp));
	else if (i == 12)
		data->envp = ft_export(data->rdl_args, data->envp, &(data->status));
	else if (i == 13)
		data->status = ft_echo(data->rdl_args);
	else if (i == 14)
		data->status = ft_env(data->rdl_args, data->envp, data->env_paths);
	else if (i == 15)
		data->envp = ft_unset(data->rdl_args, data->envp, &(data->status));
	else if (i == 16)
		data->status = ft_exit(data->rdl_args, data->envp, &(data->status), &(data->exit));
  	free_all(cmds);
	if (i > 9)
		return (1);
	return (0);
}

int	execute_command(char *path, t_data *data)
{
	int	child_pid = 0;
	int	child_info = 0;

	if (!(data->is_a_pipe))
	{
		child_pid = fork();
	}
	if (child_pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	if (!child_pid || data->is_a_pipe)
	{
		sigaction(SIGINT, &(data->OLD_SIG_INT), NULL);
        sigaction(SIGQUIT, &(data->OLD_SIG_QUIT), NULL);
		execve(path, data->rdl_args, data->envp);
		perror("execve");
		// free allocated memory
		exit(errno);
	}
	else
	{
		if (sigaction(SIGINT, &(data->S_SIG_IGN), NULL) == -1)
			return (perror(""), errno);
		signal(SIGINT, SIG_IGN);
		wait(&child_info);
		if (sigaction(SIGINT, &(data->SIG_INT), NULL) == -1)
			return (perror(""), errno);
		if (WIFEXITED(child_info))
			data->status = WEXITSTATUS(child_info);
		else if (WIFSIGNALED(child_info))
		{
			data->status = ((child_info & 127) + 128);
			if (!data->is_a_pipe && data->status == 131)
			{
				ft_putstr("Quit (core dumped)\n", 1);
			}
			else if (!data->is_a_pipe && data->status == 130)
			{
				write(1, "\n", 1);
				signal_fun(2);
			}
		}
	}
	return (0);
	//return (200);
}
