/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:11 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 12:15:58 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*get_data(void *p)
{
	static void	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}

static int	assign_std_in_out_err(t_data *data)
{
	data->fd0 = dup(STDIN_FILENO);
	if (data->fd0 == -1)
		return (perror(""), 1);
	data->fd1 = dup(STDOUT_FILENO);
	if (data->fd1 == -1)
		return (close(data->fd0), perror(""), 1);
	data->fd2 = dup(STDERR_FILENO);
	if (data->fd2 == -1)
		return (close(data->fd0), close(data->fd1), perror(""), 1);
	return (0);
}

static char	*get_cwd(t_data *data)
{
	char	*p;
	char	*temp;
	char	*var_pwd;

	p = NULL;
	p = getcwd(p, 0);
	if (!p)
		return (perror("getcwd"), NULL);
	temp = p;
	p = ft_strdup_env(p);
	free(temp);
	var_pwd = ft_strjoin("PWD=", p);
	if (ft_var_exists(var_pwd, data->envp))
	{
		data->envp = ft_duplicate_add_s(data->envp, var_pwd);
	}
	return (p);
}

void	ft_setup(t_data *data)
{
	char	**built_ins;
	char	*var_pwd;

	get_data(data);
	ft_memset(data, 0, sizeof(t_data));
	if (assign_std_in_out_err(data))
		exit(errno);
	data->envp = ft_duplicate(__environ);
	built_ins = ft_split("pwd,cd,export,echo,env,unset,exit", ',');
	data->built_ins = ft_duplicate(built_ins);
	data->cwd = get_cwd(data);
	var_pwd = ft_strjoin("PWD=", data->cwd);
	if (ft_var_exists(var_pwd, data->envp))
		data->envp = ft_duplicate_add_s(data->envp, var_pwd);
	sigemptyset(&(data->s_sig_ign.sa_mask));
	data->s_sig_ign.sa_flags = SA_RESTART;
	data->s_sig_ign.sa_handler = SIG_IGN;
	sigemptyset(&(data->sig_int.sa_mask));
	data->sig_int.sa_flags = SA_RESTART;
	data->sig_int.sa_handler = signal_handler;
	sigemptyset(&(data->s_sig_dfl.sa_mask));
	data->s_sig_dfl.sa_flags = SA_RESTART;
	data->s_sig_dfl.sa_handler = SIG_DFL;
	sigaction(SIGINT, &(data->sig_int), &(data->old_sig_int));
	sigaction(SIGQUIT, &(data->s_sig_ign), &(data->old_sig_quit));
}
