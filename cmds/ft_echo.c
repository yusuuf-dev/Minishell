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
// check \t shenanigas 
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

static void    print_envp_var(char *var ,char **envp)
{
    int     i;
    int     j;

    var++;
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(var,envp[i],ft_strlen(var)))
        {
            j = 0;
            while(envp[i][j])
            {
                if (envp[i][j] == '=')
                {
                    j++;
                    while (envp[i][j++])
                        printf("%c",envp[i][j]);
                    return;
                }
                j++;
            }
        }
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
        if (found_q(p[i],'\"'))
            print_rm_q(p[i],'\"');
        else if (found_q(p[i],'\''))
            print_rm_q(p[i],'\'');
        else if (p[i][0] == '$' && p[i][1] && p[i][1] != '$')
            print_envp_var(p[i],envp);
        else
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
/*int     ft_echo(int argc, char **p, char **envp)
{
	size_t	i = 1;

	(void)argc;
	(void)envp;
	if (p[i] && !ft_strncmp("-n", p[i], 2) && !p[i][2])
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
}*/

