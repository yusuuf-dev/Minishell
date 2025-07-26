/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:32:45 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/26 10:40:45 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_dup_fds(void)
{
	t_data	*data;

	data = get_data(NULL);
	close(data->fd0);
	close(data->fd1);
	close(data->fd2);
}
