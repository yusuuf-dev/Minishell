/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 11:29:22 by asoufian          #+#    #+#             */
/*   Updated: 2025/07/24 14:34:15 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_data *data)
{
	char	*p;

	p = NULL;
	if (!data->cwd)
	{
		p = getcwd(p, 0);
		if (!p)
		{
			return (perror("pwd: getcwd: "), 1);
		}
		data->cwd = ft_strdup_env(p);
		free(p);
	}
	ft_putstr(data->cwd, 1);
	write(1, "\n", 1);
	return (0);
}
