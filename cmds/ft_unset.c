/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:30:35 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/24 14:40:18 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_var_from_env(t_data *data, size_t ar)
{
	size_t	i;

	i = 0;
	while (data->envp[i])
	{
		if (!c_strncmp(data->envp[i], data->rdl_args[ar]))
		{
			free_ft_malloc(data->envp[i], 1);
			while (data->envp[i])
			{
				data->envp[i] = data->envp[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

int	ft_unset(t_data *data)
{
	size_t	ar;

	ar = 1;
	while (data->rdl_args[ar])
	{
		if (data->rdl_args[ar] && valid_var(data->rdl_args[ar]))
			ar++;
		if (!data->rdl_args[ar])
			return (0);
		remove_var_from_env(data, ar);
		ar++;
	}
	return (0);
}
