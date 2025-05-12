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

static int nl_parm(char *s)
{
    size_t i;

    if (s[0] != '-')
        return(0);
    i = 1;
    while(s[i])
    {
        if (s[i] != 'n')
            return(0);
        i++;
    }
    return(1);
}

int     ft_echo( char **p)
{
	size_t	i = 1;

    while (p[i] && nl_parm(p[i]))
        i++;
    while (p[i])
    {
        printf("%s",p[i]);
        if(p[i + 1])
            printf(" ");
        i++;
    }
    if(!p[1] || !nl_parm(p[1]))
	{
    	printf("\n");
	}
	return (0);
}

