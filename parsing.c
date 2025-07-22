#include "minishell.h"

int			execute_command(char *path, t_data *data);
static int	ft_built_in_cmd(t_data *data);

static  int executable(t_data *data, int mode)
{
	int is_a_file;

	is_a_file = 0;
	if (!data->rdl_args || !data->rdl_args[0])
		return (1);
    if (!(ft_strchr(data->rdl_args[0], '/')) && !mode)
    {
		return (0);
	}
	is_a_file = open(data->rdl_args[0], O_DIRECTORY); // check for errno in case open fails for some reason, and return error ?
	if (is_a_file != -1)
	{
		return (data->status = 126, close(is_a_file), ft_putstr("minishell: ", 2), ft_putstr(data->rdl_args[0], 2), ft_putstr(": Is a directory\n", 2), 1);
	}
    if (access(data->rdl_args[0], F_OK) == -1)
    {
        perror("minishell");
        return(data->status = 127, 127);
    }
    if (access(data->rdl_args[0], X_OK) == 0)
        return (execute_command(NULL, data));
    else
        perror("minishell");
    return(data->status = 126, 1);
}

static int	is_file_executable(t_data *data, char *path, char **msg)
{
	int		is_a_file;

	is_a_file = 0;
	if (!access(path, X_OK))
	{
		is_a_file = open(path, O_DIRECTORY);
		if (is_a_file == -1) // check for errno
		{
			execute_command(path, data); // need to do cleanup since this now returns on error
			return (1);
		}
		close(is_a_file);
	}
	else
	{
		if (!(*msg))
		{
			*msg = ft_strjoin("minishell: ", path);
			*msg = ft_strjoinf(*msg, ": Permission denied");
			*msg = ft_strjoinf(*msg, "\n");
		}
		data->status = 126;
	}
	return (0);
}

static int	cmd_exist_in_path(t_data *data, char *env)
{
	char	*path;
	char	*msg;
	int		i;

	env = ft_getenv("PATH", data->envp, &(data->status));
	if (!env)
		return (data->env_paths = NULL, executable(data, 1), 0);//In case we unset the PATH later, the pointer will be pointing to a non-valid memory (dangling pointer)
	data->env_paths = ft_split(env, ':');
	i = 0;
	msg = NULL;
	while (env && data->env_paths[i])
	{
		path = ft_strjoinf(ft_strjoin(data->env_paths[i], "/"), data->rdl_args[0]);
		if (!access(path, F_OK))
		{
			if (is_file_executable(data, path, &msg))
				return(0);
		}
		i++;
	}
	if (data->status != 126)
		return (data->status = 127, ft_putstr(data->rdl_args[0], 2), ft_putstr(": command not found\n", 2), 0);
	else
		ft_putstr(msg, 2);
	return (0);
}

void	parsing(t_data *data)
{

  //  if (found_q(data->p_rdl) == -1) // check if the quotes are closed;
   //     {return (ft_putstr("Error unclosed quotes\n", 2), data->envp);}
	//ft_space(data->p_rdl);
	//if(parse_redirection(&(data->p_rdl), &(data->status), data->envp, data)) // this also removes spaces;
	// if(parse_redirection(&(data->p_rdl), data))
	//  	return (data->envp);
	redirections_parsing(data);
	if (ft_redis_execute(data))
		return ;
	// data->dup_rdl = ft_strdup(data->p_rdl);
    // data->rdl_args = c_split(data->p_rdl,' ', data->envp, &(data->status));
	if (!data->p_rdl || !data->p_rdl[0])
		return ;
	data->rdl_args = NULL; // important to set it NULL because will need it again with new promt that only free it and doesn't set it to NULL
	custom_split(data->p_rdl, data, 0, 0);
	
	if (executable(data, 0)) // next
		return ;
	if (ft_built_in_cmd(data))
		return ;
	cmd_exist_in_path(data, NULL);
	return ;
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
	{
		data->envp = ft_new_export(data);
		//data->envp = ft_export(data->rdl_args, data->envp, &(data->status));
	}
	else if (i == 13)
		data->status = ft_echo(data->rdl_args);
	else if (i == 14)
		ft_env(data); // change this
		//data->status = ft_env(data->rdl_args, data->envp, data->env_paths); // change this
	else if (i == 15)
		data->status = ft_unset(data);
	//	data->envp = ft_unset(data->rdl_args, data->envp, &(data->status));
	else if (i == 16)
		data->status = ft_exit(data->rdl_args, &(data->status), &(data->exit));
  	//free_all(cmds); // needs free to be freed from the linked list.
	if (i > 9)
		return (1);
	return (0);
}

static void	reset_sig_a_reap_exit_code(t_data *data)
{
	int	child_info;

	child_info = 0;
	sigaction(SIGINT, &(data->S_SIG_IGN), NULL);
	wait(&child_info);
	sigaction(SIGINT, &(data->SIG_INT), NULL);
	if (WIFEXITED(child_info))
		data->status = WEXITSTATUS(child_info);
	else if (WIFSIGNALED(child_info))
	{
		data->status = WTERMSIG(child_info) + 128;
		if (data->status == 131)
			ft_putstr("Quit (core dumped)\n", 1);
		else if (data->status == 130)
			write(1, "\n", 1);
	}
	return ;
}

int	execute_command(char *path, t_data *data)
{
	int	child_pid;

	child_pid = 0;
	if (!(data->is_a_child))
		child_pid = fork();
	if (child_pid < 0)
	{
		print_free_exit(FORK_FAILED, errno);
	}
	if (!child_pid || data->is_a_child)
	{
		sigaction(SIGINT, &(data->OLD_SIG_INT), NULL);
        sigaction(SIGQUIT, &(data->OLD_SIG_QUIT), NULL);
		if (path)
			execve(path, data->rdl_args, data->envp);
		else
			execve(data->rdl_args[0], data->rdl_args, data->envp);
		print_free_exit(EXECVE_FAILED, errno);
	}
	else
		reset_sig_a_reap_exit_code(data);
	return (200);
}
