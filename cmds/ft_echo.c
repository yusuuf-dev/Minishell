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

int     valid_parm(char *s)
{
    int     i;

    i = 0;
    if (s[i] != '-' || s[i + 1] != 'n')
        return (0);
    i++;
    while (s[i] == 'n')
        i++;
    if (s[i])
        return(0);
    return(1);
}

int     ft_echo( char **p)
{
	size_t	i;

    i = 1;
    while (p[i])
    {
        if (valid_parm(p[i]))
            i++;
        else
            break;
    }
    while (p[i])
    {
        printf("%s",p[i]);
        if(p[i + 1])
            printf(" ");
        i++;
    }
    if(!p[1] || !valid_parm(p[1]))
	{
    	printf("\n");
	}
	return (0);
}

