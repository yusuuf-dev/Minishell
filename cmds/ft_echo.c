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

static int  found_q(char *s, char q)
{
    size_t  i;
    int     found;

    i = 0;
    found = 0;
    while (s[i])
    {
        if (s[i] == q)
            found++;
        i++;
    }
    if (found % 2 != 0)
        return(0);
    return(1);
}


void    print_rm_q(char *str,char q)
{
    size_t  i;

    i = 0;
    while (str[i])
    {
        if (str[i] != q)
            write(1, &str[i], 1);
        i++;
    }
}



int     ft_echo(int argc, char **p, char **envp)
{
	size_t	i = 1;

	(void)envp;
	(void)argc;

    if (!p[i])
    	return(0);
    while (p[i] && ft_strcmp("-n", p[i]))
        i++;
    while (p[i])
    {
        printf("%s",p[i]);
        if (p[i + 1])
            write(1, " ", 1);
        i++;
    }
    if(!ft_strcmp("-n", p[1]))
	{
    	printf("\n");
	}
	return (0);
}

