/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 12:04:21 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 19:18:12 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_std_in_out_err(t_data *data)
{
	if (data->is_a_child)
		return (0);
	if (dup2(data->fd0, STDIN_FILENO) == -1)
		print_free_exit(DUP_FAILED, errno);
	if (dup2(data->fd1, STDOUT_FILENO) == -1)
		print_free_exit(DUP_FAILED, errno);
	if (dup2(data->fd2, STDERR_FILENO) == -1)
		print_free_exit(DUP_FAILED, errno);
	return (0);
}

static void	signals_readline(t_data *data)
{
	sigaction(SIGINT, &(data->sig_int), NULL);
	sigaction(SIGQUIT, &(data->s_sig_ign), NULL);
	data->p_rdl = ft_read_line_gnl(1);
	if (signal_fun(-1))
	{
		data->status = 130;
		signal_fun(0);
	}
	if (!data->p_rdl)
	{
		if (isatty(STDIN_FILENO))
			ft_putstr("exit\n", 2);
		rl_clear_history();
		config_malloc(NULL, 0, 2);
		exit(data->status);
	}
}

int	main(void)
{
	t_data	data;

	ft_setup(&data);
	while (!(data.exit) && !(data.is_a_child))
	{
		signals_readline(&data);
		if (data.p_rdl[0] && !check_syntax(&data))
		{
			here_doc(&data);
			if (data.p_rdl && data.p_rdl[0])
			{
				if (found_pipe(data.p_rdl))
				{
					data.segments = skip_quotes_split(data.p_rdl, '|');
					ft_pipes(&data);
				}
				if (data.p_rdl)
					parsing(&data);
				reset_std_in_out_err(&data);
			}
		}
		memset(&data, 0, (sizeof(void *) * PTR_TO_NULL));
		config_malloc(NULL, 0, 0);
	}
	return (rl_clear_history(), config_malloc(NULL, 0, 2), data.status);
}
