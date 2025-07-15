/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-you <yoel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:17:55 by yoel-you          #+#    #+#             */
/*   Updated: 2025/07/14 17:17:56 by yoel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_parm(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-' || s[i + 1] != 'n')
		return (0);
	i++;
	while (s[i] == 'n')
		i++;
	if (s[i])
		return (0);
	return (1);
}

int	ft_echo(char **p)
{
	size_t	i;

	i = 1;
	while (p[i])
	{
		if (valid_parm(p[i]))
			i++;
		else
			break ;
	}
	while (p[i])
	{
		ft_putstr(p[i], 1);
		if (p[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!p[1] || !valid_parm(p[1]))
	{
		write(1, "\n", 1);
	}
	return (0);
}
