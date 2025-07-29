/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:49:13 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 18:53:56 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_sig_a_reap_exit_code(t_data *data)
{
	int	child_info;

	child_info = 0;
	sigaction(SIGINT, &(data->s_sig_ign), NULL);
	wait(&child_info);
	sigaction(SIGINT, &(data->sig_int), NULL);
	if (WIFEXITED(child_info))
		data->status = WEXITSTATUS(child_info);
	else if (WIFSIGNALED(child_info))
	{
		data->status = WTERMSIG(child_info) + 128;
		if (data->status == 131)
			ft_putstr("Quit (core dumped)\n", 2);
		else if (data->status == 130)
			write(1, "\n", 2);
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
		if (!child_pid && !data->is_a_child)
			close_dup_fds();
		sigaction(SIGINT, &(data->old_sig_int), NULL);
		sigaction(SIGQUIT, &(data->old_sig_quit), NULL);
		if (path)
			execve(path, data->rdl_args, data->envp);
		else
			execve(data->rdl_args[0], data->rdl_args, data->envp);
		print_free_exit(EXECVE_FAILED, errno);
	}
	else
		reset_sig_a_reap_exit_code(data);
	return (1);
}
