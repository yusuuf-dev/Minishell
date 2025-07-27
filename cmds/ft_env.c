/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:00:03 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/24 14:39:08 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strchr(data->envp[i], '='))
		{
			write(1, data->envp[i], ft_strlen(data->envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return ;
}
