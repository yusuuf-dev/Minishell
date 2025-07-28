/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:26:06 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 18:35:22 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	executable(t_data *data, int mode)
{
	int	is_a_file;

	is_a_file = 0;
	if (!data->rdl_args || !data->rdl_args[0])
		return (1);
	if (!(ft_strchr(data->rdl_args[0], '/')) && !mode)
		return (0);
	is_a_file = open(data->rdl_args[0], O_DIRECTORY);
	if (is_a_file != -1)
	{
		data->status = 126;
		return (close(is_a_file), ft_putstr("minishell: ", 2),
			ft_putstr(data->rdl_args[0], 2), ft_putstr(": Is a directory\n", 2),
			1);
	}
	if (access(data->rdl_args[0], F_OK) == -1)
	{
		perror(ft_strjoin("minishell: ", data->rdl_args[0]));
		return (data->status = 127, 127);
	}
	if (access(data->rdl_args[0], X_OK) == 0)
		return (execute_command(NULL, data));
	else
		perror(ft_strjoin("minishell: ", data->rdl_args[0]));
	return (data->status = 126, 1);
}

static int	is_file_executable(t_data *data, char *path, char **msg)
{
	int	is_a_file;

	is_a_file = 0;
	if (!access(path, X_OK))
	{
		is_a_file = open(path, O_DIRECTORY);
		if (is_a_file == -1)
		{
			execute_command(path, data);
			return (1);
		}
		close(is_a_file);
	}
	else
	{
		if (!(*msg))
		{
			*msg = ft_strjoin("minishell: ", path);
			*msg = ft_strjoin(*msg, ": Permission denied");
			*msg = ft_strjoin(*msg, "\n");
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

	data->status = 0;
	env = ft_getenv("PATH", data->envp, &(data->status));
	if (!env)
		return (data->env_paths = NULL, executable(data, 1), 0);
	data->env_paths = ft_split(env, ':');
	i = 0;
	msg = NULL;
	while (env && data->env_paths[i])
	{
		path = ft_strjoin(ft_strjoin(data->env_paths[i++], "/"),
				data->rdl_args[0]);
		if (!access(path, F_OK))
		{
			if (is_file_executable(data, path, &msg))
				return (0);
		}
	}
	if (data->status != 126)
		return (data->status = 127, ft_putstr(data->rdl_args[0], 2),
			ft_putstr(": command not found\n", 2), 0);
	return (ft_putstr(msg, 2), 0);
}

static int	ft_built_in_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (i < 10 && data->built_ins[i])
	{
		if (ft_strcmp(data->built_ins[i++], data->rdl_args[0]))
			i += 9;
	}
	if (i == 10)
		data->status = ft_pwd(data);
	else if (i == 11)
		data->status = ft_cd(data->rdl_args, data->rdl_args[1], data, 0);
	else if (i == 12)
		data->envp = ft_new_export(data);
	else if (i == 13)
		data->status = ft_echo(data->rdl_args);
	else if (i == 14)
		ft_env(data);
	else if (i == 15)
		data->status = ft_unset(data);
	else if (i == 16)
		data->exit = ft_exit(data->rdl_args, data);
	if (i > 9)
		return (1);
	return (0);
}

void	parsing(t_data *data)
{
	redirections_parsing(data);
	if (ft_redis_execute(data))
		return ;
	if (!data->p_rdl || !data->p_rdl[0])
		return ;
	data->rdl_args = NULL;
	custom_split(data->p_rdl, data, 0, 0);
	if (executable(data, 0))
		return ;
	if (ft_built_in_cmd(data))
		return ;
	cmd_exist_in_path(data, NULL);
	return ;
}
