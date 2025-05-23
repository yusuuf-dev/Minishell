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
static int	ft_built_in_cmd(t_data *data);

int     c_strncmp(const char *s1, const char *s2)
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
	int is_a_file = 0;

    if (!(rdl_args[0][0] == '.' || (ft_strchr(rdl_args[0], '/'))))// && rdl_args[0][ft_strlen(rdl_args[0] - 1)] != '/')))
    {    return (0);}
	is_a_file = open(rdl_args[0], O_DIRECTORY);
	if (is_a_file != -1)
		{return (close(is_a_file), ft_putstr("minishell: ", 2), ft_putstr(rdl_args[0], 2), ft_putstr(": Is a directory\n", 2), 126);} // need to set the status to 126;
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

void	parsing(t_data *data)
{
    int		i = 0;
	char	*path;

    if (found_q(data->p_rdl) == -1) // check if the quotes are closed;
    {
		ft_putstr("Error unclosed quotes\n", 2);
		return;
	}
	ft_space(data->p_rdl); 
	if(parse_redirection(data->rdl_args, data->status, data->envp)) // this also removes spaces;
	 	return;
	//*p = convert_env_var(*p, envp);
	if (is_execute_file(data->rdl_args,data->envp))
		return;
	if (!ft_built_in_cmd(data))
	{
		while (data->env_paths[i])
		{
			path = ft_strjoinf(ft_strjoin(data->env_paths[i], "/"),data->rdl_args[0]);
			if (!access(path, F_OK) && !access(path, X_OK))
			{
				data->exit = execute_command(path, data->rdl_args, data->envp);
				return;
			}
			i++;
		}
		ft_putstr("minishell: command not found: ", 2);
		ft_putstr(data->rdl_args[0], 2);
		ft_putstr("\n", 2);
	}
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
        {
			    i += 9;
          //  ft_excmd_built(rdl_args, i, envp, env_paths);
          //  return(1);
        }
        i++;
	}
	if (i == 10)
		data->exit = ft_pwd(data->rdl_args, data->envp);
	else if (i == 11)
		data->exit = ft_cd(data->rdl_args, &data->envp);
	else if (i == 12)
		data->envp = ft_export(data->rdl_args, data->envp, data->status);
	else if (i == 13)
		data->exit = ft_echo(data->rdl_args);
	else if (i == 14)
		data->exit = ft_env(data->rdl_args, data->envp, data->env_paths);
	else if (i == 15)
		data->envp = ft_unset(data->rdl_args, data->envp, data->status);
	else if (i == 16)
	{
		data->exit = ft_exit(data);
		//if (*status)
		//	*s_exit = *status;
		//if (*status == 2)
		//	*s_exit = 0;
	//	else
		data->exit = 1;
	}
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
	if (child_pid < 0)
	{
		perror("fork");
		exit(errno);
	}
	if (!child_pid)
	{
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
		//printf("child waiting status in excute_command: %d\n",waitpid(child_pid, &child_info, 0));
	}
	if (WIFEXITED(child_info))
		return (WEXITSTATUS(child_info));
	return (-1);
}