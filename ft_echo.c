/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoufian <asoufian@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:23:00 by asoufian          #+#    #+#             */
/*   Updated: 2025/04/13 10:57:07 by asoufian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_echo(int argc, char **p, char **envp)
{
	size_t	i = 1;

	(void)argc;
	(void)envp;
	if (!ft_strcmp("-n", p[i], 2) && !p[i][2])
	{
		i++;
		while (p[i])
		{
			if (i > 2)
				printf(" ");
			printf("%s", p[i]);
			i++;
		}
	}
	else
	{
		while (p[i])
		{
			if (i > 1)
				printf(" ");
			printf("%s", p[i]);
			i++;
		}
		printf("\n");
	}
        return (0);
}

