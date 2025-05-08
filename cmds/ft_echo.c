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

#include "../minishell.h"

int     ft_echo( char **p, char **envp)
{
	size_t	i = 1;

	(void)envp;


    if (!p[i])
    	return(0);
    while (p[i] && ft_strcmp("-n", p[i]))
        i++;
    while (p[i])
    {
        printf("%s",p[i]);
        if(p[i + 1])
            printf(" ");
        i++;
    }
    if(!ft_strcmp("-n", p[1]))
	{
    	printf("\n");
	}
	return (0);
}

